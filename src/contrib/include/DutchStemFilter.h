/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2009-2011 Alan Wright. All rights reserved.
// Distributable under the terms of either the Apache License (Version 2.0)
// or the GNU Lesser General Public License.
/////////////////////////////////////////////////////////////////////////////

#ifndef DUTCHSTEMFILTER_H
#define DUTCHSTEMFILTER_H

#include "LuceneContrib.h"
#include "TokenFilter.h"

namespace Lucene
{
    /// A {@link TokenFilter} that stems Dutch words.
    ///
    /// It supports a table of words that should not be stemmed at all.  The stemmer
    /// used can be changed at runtime after the filter object is created (as long
    /// as it is a {@link DutchStemmer}).
    ///
    /// To prevent terms from being stemmed use an instance of {@link
    /// KeywordMarkerFilter} or a custom {@link TokenFilter} that sets the {@link
    /// KeywordAttribute} before this {@link TokenStream}.
    ///
    /// @see KeywordMarkerFilter
    /// @deprecated Use {@link SnowballFilter} with {@link DutchStemmer} instead,
    /// which has the same functionality.
    class LPPCONTRIBAPI DutchStemFilter : public TokenFilter
    {
    public:
        DutchStemFilter(TokenStreamPtr input);

        /// Builds a DutchStemFilter that uses an exclusion table.
        /// @deprecated use {@link KeywordAttribute} with {@link KeywordMarkerFilter} instead
        DutchStemFilter(TokenStreamPtr input, HashSet<String> exclusiontable);

        /// Builds a DutchStemFilter that uses an exclusion table and dictionary of word stem
        /// pairs, that overrule the algorithm.
        /// @deprecated use {@link KeywordAttribute} with {@link KeywordMarkerFilter} instead.
        DutchStemFilter(TokenStreamPtr input, HashSet<String> exclusiontable, MapStringString stemdictionary);

        virtual ~DutchStemFilter();

        LUCENE_CLASS(DutchStemFilter);

    protected:
        /// {@link DutchStemmer} in use by this filter.
        DutchStemmerPtr stemmer;

        HashSet<String> exclusions;
        CharTermAttributePtr termAtt;
        KeywordAttributePtr keywordAttr;

    public:
        virtual bool incrementToken();

        /// Set a alternative/custom {@link DutchStemmer} for this filter.
        void setStemmer(DutchStemmerPtr stemmer);

        /// Set an alternative exclusion list for this filter.
        /// @deprecated use {@link KeywordAttribute} with {@link KeywordMarkerFilter} instead.
        void setExclusionSet(HashSet<String> exclusiontable);

        /// Set dictionary for stemming, this dictionary overrules the algorithm, so you can
        /// correct for a particular unwanted word-stem pair.
        void setStemDictionary(MapStringString dict);
    };
}

#endif

