#ifndef TESTPARSER_H
#define TESTPARSER_H

#include "gmock/gmock.h"
#include "parser.h"
#include "tokenizer.h"

using namespace testing;

class TestParser : public Test
{
public:
    TestParser()
        :parser(&tokenizer)
    {}

    ~TestParser()
    {}

    void SetUp()
    {

    }

    void TearDown()
    {

    }

    Tokenizer tokenizer;
    Parser parser;
};

#endif // TESTPARSER_H
