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
        :parser(&tokenizer), evaluator(&parser)
    {}
    ~TestEvaluator()
    {}

    Tokenizer tokenizer;
    Parser parser;
    Evaluator evaluator;
};

#endif // TESTEVALUATOR_H
