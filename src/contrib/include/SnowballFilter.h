/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2009-2011 Alan Wright. All rights reserved.
// Distributable under the terms of either the Apache License (Version 2.0)
// or the GNU Lesser General Public License.
/////////////////////////////////////////////////////////////////////////////

#ifndef SNOWBALLFILTER_H
#define SNOWBALLFILTER_H

#include "LuceneContrib.h"
#include "TokenFilter.h"

struct sb_stemmer;

namespace Lucene
{
    /// A filter that stems words using a Snowball-generated stemmer.
    ///
    /// NOTE: SnowballFilter expects lowercased text.
    /// <ul>
    ///    <li>For the Turkish language, see {@link TurkishLowerCaseFilter}.
    ///    <li>For other languages, see {@link LowerCaseFilter}.
    /// </ul>
    class LPPCONTRIBAPI SnowballFilter : public TokenFilter
    {
    public:
        SnowballFilter(TokenStreamPtr input, const String& name);
        virtual ~SnowballFilter();

        LUCENE_CLASS(SnowballFilter);

    protected:
        struct sb_stemmer* stemmer;
        UTF8ResultPtr utf8Result;
        CharTermAttributePtr termAtt;
        KeywordAttributePtr keywordAttr;

    public:
        virtual bool incrementToken();
    };
}

#endif

