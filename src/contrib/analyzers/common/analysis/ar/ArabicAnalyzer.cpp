/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2009-2011 Alan Wright. All rights reserved.
// Distributable under the terms of either the Apache License (Version 2.0)
// or the GNU Lesser General Public License.
/////////////////////////////////////////////////////////////////////////////

#include "ContribInc.h"
#include "ArabicAnalyzer.h"
#include "ArabicLetterTokenizer.h"
#include "LowerCaseFilter.h"
#include "StopFilter.h"
#include "ArabicNormalizationFilter.h"
#include "ArabicStemFilter.h"
#include "StandardTokenizer.h"
#include "KeywordMarkerFilter.h"
#include "StringUtils.h"

namespace Lucene
{
    /// Default Arabic stopwords in UTF-8 format.
    ///
    /// Generated from http://members.unine.ch/jacques.savoy/clef/index.html
    /// The stopword list is BSD-Licensed.
    const uint8_t ArabicAnalyzer::DEFAULT_STOPWORD_FILE[] = 
    {
        0xd9, 0x85, 0xd9, 0x86, 0x0a, 0xd9, 0x88, 0xd9, 0x85, 0xd9, 0x86, 0x0a, 0xd9, 0x85, 0xd9, 0x86, 
        0xd9, 0x87, 0xd8, 0xa7, 0x0a, 0xd9, 0x85, 0xd9, 0x86, 0xd9, 0x87, 0x0a, 0xd9, 0x81, 0xd9, 0x8a, 
        0x0a, 0xd9, 0x88, 0xd9, 0x81, 0xd9, 0x8a, 0x0a, 0xd9, 0x81, 0xd9, 0x8a, 0xd9, 0x87, 0xd8, 0xa7, 
        0x0a, 0xd9, 0x81, 0xd9, 0x8a, 0xd9, 0x87, 0x0a, 0xd9, 0x88, 0x0a, 0xd9, 0x81, 0x0a, 0xd8, 0xab, 
        0xd9, 0x85, 0x0a, 0xd8, 0xa7, 0xd9, 0x88, 0x0a, 0xd8, 0xa3, 0xd9, 0x88, 0x0a, 0xd8, 0xa8, 0x0a, 
        0xd8, 0xa8, 0xd9, 0x87, 0xd8, 0xa7, 0x0a, 0xd8, 0xa8, 0xd9, 0x87, 0x0a, 0xd8, 0xa7, 0x0a, 0xd8, 
        0xa3, 0x0a, 0xd8, 0xa7, 0xd9, 0x89, 0x0a, 0xd8, 0xa7, 0xd9, 0x8a, 0x0a, 0xd8, 0xa3, 0xd9, 0x8a, 
        0x0a, 0xd8, 0xa3, 0xd9, 0x89, 0x0a, 0xd9, 0x84, 0xd8, 0xa7, 0x0a, 0xd9, 0x88, 0xd9, 0x84, 0xd8, 
        0xa7, 0x0a, 0xd8, 0xa7, 0xd9, 0x84, 0xd8, 0xa7, 0x0a, 0xd8, 0xa3, 0xd9, 0x84, 0xd8, 0xa7, 0x0a, 
        0xd8, 0xa5, 0xd9, 0x84, 0xd8, 0xa7, 0x0a, 0xd9, 0x84, 0xd9, 0x83, 0xd9, 0x86, 0x0a, 0xd9, 0x85, 
        0xd8, 0xa7, 0x0a, 0xd9, 0x88, 0xd9, 0x85, 0xd8, 0xa7, 0x0a, 0xd9, 0x83, 0xd9, 0x85, 0xd8, 0xa7, 
        0x0a, 0xd9, 0x81, 0xd9, 0x85, 0xd8, 0xa7, 0x0a, 0xd8, 0xb9, 0xd9, 0x86, 0x0a, 0xd9, 0x85, 0xd8, 
        0xb9, 0x0a, 0xd8, 0xa7, 0xd8, 0xb0, 0xd8, 0xa7, 0x0a, 0xd8, 0xa5, 0xd8, 0xb0, 0xd8, 0xa7, 0x0a, 
        0xd8, 0xa7, 0xd9, 0x86, 0x0a, 0xd8, 0xa3, 0xd9, 0x86, 0x0a, 0xd8, 0xa5, 0xd9, 0x86, 0x0a, 0xd8, 
        0xa7, 0xd9, 0x86, 0xd9, 0x87, 0xd8, 0xa7, 0x0a, 0xd8, 0xa3, 0xd9, 0x86, 0xd9, 0x87, 0xd8, 0xa7, 
        0x0a, 0xd8, 0xa5, 0xd9, 0x86, 0xd9, 0x87, 0xd8, 0xa7, 0x0a, 0xd8, 0xa7, 0xd9, 0x86, 0xd9, 0x87, 
        0x0a, 0xd8, 0xa3, 0xd9, 0x86, 0xd9, 0x87, 0x0a, 0xd8, 0xa5, 0xd9, 0x86, 0xd9, 0x87, 0x0a, 0xd8, 
        0xa8, 0xd8, 0xa7, 0xd9, 0x86, 0x0a, 0xd8, 0xa8, 0xd8, 0xa3, 0xd9, 0x86, 0x0a, 0xd9, 0x81, 0xd8, 
        0xa7, 0xd9, 0x86, 0x0a, 0xd9, 0x81, 0xd8, 0xa3, 0xd9, 0x86, 0x0a, 0xd9, 0x88, 0xd8, 0xa7, 0xd9, 
        0x86, 0x0a, 0xd9, 0x88, 0xd8, 0xa3, 0xd9, 0x86, 0x0a, 0xd9, 0x88, 0xd8, 0xa5, 0xd9, 0x86, 0x0a, 
        0xd8, 0xa7, 0xd9, 0x84, 0xd8, 0xaa, 0xd9, 0x89, 0x0a, 0xd8, 0xa7, 0xd9, 0x84, 0xd8, 0xaa, 0xd9, 
        0x8a, 0x0a, 0xd8, 0xa7, 0xd9, 0x84, 0xd8, 0xb0, 0xd9, 0x89, 0x0a, 0xd8, 0xa7, 0xd9, 0x84, 0xd8, 
        0xb0, 0xd9, 0x8a, 0x0a, 0xd8, 0xa7, 0xd9, 0x84, 0xd8, 0xb0, 0xd9, 0x8a, 0xd9, 0x86, 0x0a, 0xd8, 
        0xa7, 0xd9, 0x84, 0xd9, 0x89, 0x0a, 0xd8, 0xa7, 0xd9, 0x84, 0xd9, 0x8a, 0x0a, 0xd8, 0xa5, 0xd9, 
        0x84, 0xd9, 0x89, 0x0a, 0xd8, 0xa5, 0xd9, 0x84, 0xd9, 0x8a, 0x0a, 0xd8, 0xb9, 0xd9, 0x84, 0xd9, 
        0x89, 0x0a, 0xd8, 0xb9, 0xd9, 0x84, 0xd9, 0x8a, 0xd9, 0x87, 0xd8, 0xa7, 0x0a, 0xd8, 0xb9, 0xd9, 
        0x84, 0xd9, 0x8a, 0xd9, 0x87, 0x0a, 0xd8, 0xa7, 0xd9, 0x85, 0xd8, 0xa7, 0x0a, 0xd8, 0xa3, 0xd9, 
        0x85, 0xd8, 0xa7, 0x0a, 0xd8, 0xa5, 0xd9, 0x85, 0xd8, 0xa7, 0x0a, 0xd8, 0xa7, 0xd9, 0x8a, 0xd8, 
        0xb6, 0xd8, 0xa7, 0x0a, 0xd8, 0xa3, 0xd9, 0x8a, 0xd8, 0xb6, 0xd8, 0xa7, 0x0a, 0xd9, 0x83, 0xd9, 
        0x84, 0x0a, 0xd9, 0x88, 0xd9, 0x83, 0xd9, 0x84, 0x0a, 0xd9, 0x84, 0xd9, 0x85, 0x0a, 0xd9, 0x88, 
        0xd9, 0x84, 0xd9, 0x85, 0x0a, 0xd9, 0x84, 0xd9, 0x86, 0x0a, 0xd9, 0x88, 0xd9, 0x84, 0xd9, 0x86, 
        0x0a, 0xd9, 0x87, 0xd9, 0x89, 0x0a, 0xd9, 0x87, 0xd9, 0x8a, 0x0a, 0xd9, 0x87, 0xd9, 0x88, 0x0a, 
        0xd9, 0x88, 0xd9, 0x87, 0xd9, 0x89, 0x0a, 0xd9, 0x88, 0xd9, 0x87, 0xd9, 0x8a, 0x0a, 0xd9, 0x88, 
        0xd9, 0x87, 0xd9, 0x88, 0x0a, 0xd9, 0x81, 0xd9, 0x87, 0xd9, 0x89, 0x0a, 0xd9, 0x81, 0xd9, 0x87, 
        0xd9, 0x8a, 0x0a, 0xd9, 0x81, 0xd9, 0x87, 0xd9, 0x88, 0x0a, 0xd8, 0xa7, 0xd9, 0x86, 0xd8, 0xaa, 
        0x0a, 0xd8, 0xa3, 0xd9, 0x86, 0xd8, 0xaa, 0x0a, 0xd9, 0x84, 0xd9, 0x83, 0x0a, 0xd9, 0x84, 0xd9, 
        0x87, 0xd8, 0xa7, 0x0a, 0xd9, 0x84, 0xd9, 0x87, 0x0a, 0xd9, 0x87, 0xd8, 0xb0, 0xd9, 0x87, 0x0a, 
        0xd9, 0x87, 0xd8, 0xb0, 0xd8, 0xa7, 0x0a, 0xd8, 0xaa, 0xd9, 0x84, 0xd9, 0x83, 0x0a, 0xd8, 0xb0, 
        0xd9, 0x84, 0xd9, 0x83, 0x0a, 0xd9, 0x87, 0xd9, 0x86, 0xd8, 0xa7, 0xd9, 0x83, 0x0a, 0xd9, 0x83, 
        0xd8, 0xa7, 0xd9, 0x86, 0xd8, 0xaa, 0x0a, 0xd9, 0x83, 0xd8, 0xa7, 0xd9, 0x86, 0x0a, 0xd9, 0x8a, 
        0xd9, 0x83, 0xd9, 0x88, 0xd9, 0x86, 0x0a, 0xd8, 0xaa, 0xd9, 0x83, 0xd9, 0x88, 0xd9, 0x86, 0x0a, 
        0xd9, 0x88, 0xd9, 0x83, 0xd8, 0xa7, 0xd9, 0x86, 0xd8, 0xaa, 0x0a, 0xd9, 0x88, 0xd9, 0x83, 0xd8, 
        0xa7, 0xd9, 0x86, 0x0a, 0xd8, 0xba, 0xd9, 0x8a, 0xd8, 0xb1, 0x0a, 0xd8, 0xa8, 0xd8, 0xb9, 0xd8, 
        0xb6, 0x0a, 0xd9, 0x82, 0xd8, 0xaf, 0x0a, 0xd9, 0x86, 0xd8, 0xad, 0xd9, 0x88, 0x0a, 0xd8, 0xa8, 
        0xd9, 0x8a, 0xd9, 0x86, 0x0a, 0xd8, 0xa8, 0xd9, 0x8a, 0xd9, 0x86, 0xd9, 0x85, 0xd8, 0xa7, 0x0a, 
        0xd9, 0x85, 0xd9, 0x86, 0xd8, 0xb0, 0x0a, 0xd8, 0xb6, 0xd9, 0x85, 0xd9, 0x86, 0x0a, 0xd8, 0xad, 
        0xd9, 0x8a, 0xd8, 0xab, 0x0a, 0xd8, 0xa7, 0xd9, 0x84, 0xd8, 0xa7, 0xd9, 0x86, 0x0a, 0xd8, 0xa7, 
        0xd9, 0x84, 0xd8, 0xa2, 0xd9, 0x86, 0x0a, 0xd8, 0xae, 0xd9, 0x84, 0xd8, 0xa7, 0xd9, 0x84, 0x0a, 
        0xd8, 0xa8, 0xd8, 0xb9, 0xd8, 0xaf, 0x0a, 0xd9, 0x82, 0xd8, 0xa8, 0xd9, 0x84, 0x0a, 0xd8, 0xad, 
        0xd8, 0xaa, 0xd9, 0x89, 0x0a, 0xd8, 0xb9, 0xd9, 0x86, 0xd8, 0xaf, 0x0a, 0xd8, 0xb9, 0xd9, 0x86, 
        0xd8, 0xaf, 0xd9, 0x85, 0xd8, 0xa7, 0x0a, 0xd9, 0x84, 0xd8, 0xaf, 0xd9, 0x89, 0x0a, 0xd8, 0xac, 
        0xd9, 0x85, 0xd9, 0x8a, 0xd8, 0xb9, 0x0a
    };
    
    ArabicAnalyzer::ArabicAnalyzer(LuceneVersion::Version matchVersion) : StopwordAnalyzerBase(matchVersion, getDefaultStopSet())
    {
    }
    
    ArabicAnalyzer::ArabicAnalyzer(LuceneVersion::Version matchVersion, HashSet<String> stopwords) : StopwordAnalyzerBase(matchVersion, stopwords)
    {
    }
    
    ArabicAnalyzer::ArabicAnalyzer(LuceneVersion::Version matchVersion, HashSet<String> stopwords, HashSet<String> stemExclusionSet) : StopwordAnalyzerBase(matchVersion, stopwords)
    {
        this->stemExclusionSet = stemExclusionSet;
    }
    
    ArabicAnalyzer::~ArabicAnalyzer()
    {
    }
    
    const HashSet<String> ArabicAnalyzer::getDefaultStopSet()
    {
        static HashSet<String> stopSet;
        if (!stopSet)
        {
            String stopWords(UTF8_TO_STRING(DEFAULT_STOPWORD_FILE));
            Collection<String> words(StringUtils::split(stopWords, L"\n"));
            stopSet = HashSet<String>::newInstance(words.begin(), words.end());
        }
        return stopSet;
    }
    
    TokenStreamComponentsPtr ArabicAnalyzer::createComponents(const String& fieldName, ReaderPtr reader)
    {
        TokenizerPtr source;
        if (LuceneVersion::onOrAfter(matchVersion, LuceneVersion::LUCENE_31))
            source = newLucene<StandardTokenizer>(matchVersion, reader);
        else
            source = newLucene<ArabicLetterTokenizer>(matchVersion, reader);
        TokenStreamPtr result(newLucene<LowerCaseFilter>(matchVersion, source));
        // the order here is important: the stopword list is not normalized
        result = newLucene<StopFilter>(matchVersion, result, stopwords);
        result = newLucene<ArabicNormalizationFilter>(result);
        if (!stemExclusionSet.empty())
            result = newLucene<KeywordMarkerFilter>(result, stemExclusionSet);
        return newLucene<TokenStreamComponents>(source, newLucene<ArabicStemFilter>(result));
    }
}
