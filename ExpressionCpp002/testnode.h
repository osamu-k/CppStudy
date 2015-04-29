#ifndef TESTNODE_H
#define TESTNODE_H

#include "gmock/gmock.h"
#include "node.h"

using namespace testing;

class TestNode : public Test
{
public:
    TestNode(){}
    ~TestNode(){}

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

#endif // TESTNODE_H
