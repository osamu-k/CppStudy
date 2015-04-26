#ifndef TESTTOKENIZER_H
#define TESTTOKENIZER_H

#include "gmock/gmock.h"
#include "tokenizer.h"

using namespace testing;

class TestTokenizer : public Test {

protected:
    virtual void SetUp() {
    }
    virtual void TearDown() {
    }

    Tokenizer tokenizer;
};

#endif // TESTTOKENIZER_H
