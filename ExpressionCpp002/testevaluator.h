#ifndef TESTEVALUATOR_H
#define TESTEVALUATOR_H

#include "gmock/gmock.h"
#include "evaluator.h"
#include "parser.h"
#include "tokenizer.h"

using namespace testing;

class TestEvaluator : public Test
{
public:
    TestEvaluator()
        :parser(&tokenizer)
    {}
    ~TestEvaluator()
    {}

    Tokenizer tokenizer;
    Parser parser;
    Evaluator evaluator;

    int evaluate( string source )
    {
        Node *node = parser.parse( source );
        return evaluator.evaluate( node );
    }
};

#endif // TESTEVALUATOR_H
