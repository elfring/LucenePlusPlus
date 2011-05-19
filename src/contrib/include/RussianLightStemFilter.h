/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2009-2011 Alan Wright. All rights reserved.
// Distributable under the terms of either the Apache License (Version 2.0)
// or the GNU Lesser General Public License.
/////////////////////////////////////////////////////////////////////////////

#ifndef RUSSIANLIGHTSTEMFILTER_H
#define RUSSIANLIGHTSTEMFILTER_H

#include "LuceneContrib.h"
#include "TokenFilter.h"

namespace Lucene
{
    /// A {@link TokenFilter} that applies {@link RussianLightStemmer} to stem Russian words.
	///
	/// To prevent terms from being stemmed use an instance of {@link KeywordMarkerFilter}
	/// or a custom {@link TokenFilter} that sets the {@link KeywordAttribute} before this
	/// {@link TokenStream}.
    class LPPCONTRIBAPI RussianLightStemFilter : public TokenFilter
    {
    public:
        RussianLightStemFilter(TokenStreamPtr input);
        virtual ~RussianLightStemFilter();

        LUCENE_CLASS(RussianLightStemFilter);

    protected:
        RussianLightStemmerPtr stemmer;
        CharTermAttributePtr termAtt;
        KeywordAttributePtr keywordAttr;

    public:
        virtual bool incrementToken();
    };
}

#endif

