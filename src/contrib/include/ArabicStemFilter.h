/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2009-2011 Alan Wright. All rights reserved.
// Distributable under the terms of either the Apache License (Version 2.0)
// or the GNU Lesser General Public License.
/////////////////////////////////////////////////////////////////////////////

#ifndef ARABICSTEMFILTER_H
#define ARABICSTEMFILTER_H

#include "LuceneContrib.h"
#include "TokenFilter.h"

namespace Lucene
{
    /// A {@link TokenFilter} that applies {@link ArabicStemmer} to stem Arabic words.
    ///
    /// To prevent terms from being stemmed use an instance of {@link KeywordMarkerFilter} 
    /// or a custom {@link TokenFilter} that sets the {@link KeywordAttribute} before this 
    /// {@link TokenStream}.
    /// 
    /// @see KeywordMarkerFilter
    class LPPCONTRIBAPI ArabicStemFilter : public TokenFilter
    {
    public:
        ArabicStemFilter(TokenStreamPtr input);
        virtual ~ArabicStemFilter();
        
        LUCENE_CLASS(ArabicStemFilter);
    
    protected:
        ArabicStemmerPtr stemmer;
        CharTermAttributePtr termAtt;
        KeywordAttributePtr keywordAttr;
    
    public:
        virtual bool incrementToken();
    };
}

#endif
