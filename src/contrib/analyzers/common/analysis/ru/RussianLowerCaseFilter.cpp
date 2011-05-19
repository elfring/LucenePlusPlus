/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2009-2011 Alan Wright. All rights reserved.
// Distributable under the terms of either the Apache License (Version 2.0)
// or the GNU Lesser General Public License.
/////////////////////////////////////////////////////////////////////////////

#include "ContribInc.h"
#include "RussianLowerCaseFilter.h"
#include "CharTermAttribute.h"
#include "CharFolder.h"

namespace Lucene
{
    RussianLowerCaseFilter::RussianLowerCaseFilter(TokenStreamPtr input) : TokenFilter(input)
    {
        termAtt = addAttribute<CharTermAttribute>();
    }

    RussianLowerCaseFilter::~RussianLowerCaseFilter()
    {
    }

    bool RussianLowerCaseFilter::incrementToken()
    {
        if (input->incrementToken())
        {
            wchar_t* buffer = termAtt->bufferArray();
            int32_t length = termAtt->length();
            for (int32_t i = 0; i < length; ++i)
                buffer[i] = CharFolder::toLower(buffer[i]);
            return true;
        }
        else
            return false;
    }
}

