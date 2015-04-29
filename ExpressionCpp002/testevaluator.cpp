#include "testevaluator.h"

TEST_F( TestEvaluator, evaluatesInteger )
{
    int value = evaluator.evaluate( "123" );
    ASSERT_THAT( value, Eq(123) );
}

TEST_F( TestEvaluator, evaluatesPrifixPlus )
{
    int value = evaluator.evaluate( "+123" );
    ASSERT_THAT( value, Eq(123) );
}

TEST_F( TestEvaluator, evaluatesPrifixMinus )
{
    int value = evaluator.evaluate( "-123" );
    ASSERT_THAT( value, Eq(-123) );
}

TEST_F( TestEvaluator, evaluateMul )
{
    int value = evaluator.evaluate( "-123*456" );
    ASSERT_THAT( value, Eq(-123*456) );
}

TEST_F( TestEvaluator, evaluateDiv )
{
    int value = evaluator.evaluate( "-1234/56" );
    ASSERT_THAT( value, Eq(-1234/56) );
}

TEST_F( TestEvaluator, evaluateAdd )
{
    int value = evaluator.evaluate( "-123+456" );
    ASSERT_THAT( value, Eq(-123+456) );
}

TEST_F( TestEvaluator, evaluateSub )
{
    int value = evaluator.evaluate( "-123-456" );
    ASSERT_THAT( value, Eq(-123-456) );
}

TEST_F( TestEvaluator, evaluateNestedExpression1 )
{
    int value = evaluator.evaluate( "-123*4+567/+8" );
    ASSERT_THAT( value, Eq(-123*4+567/+8) );
}

TEST_F( TestEvaluator, evaluateNestedExpression2 )
{
    int value = evaluator.evaluate( "-123*((4+567)/+8)" );
    ASSERT_THAT( value, Eq(-123*((4+567)/+8)) );
}

TEST_F( TestEvaluator, evaluateVariable )
{
    int value1 = evaluator.evaluate( "var x = 123" );
    ASSERT_THAT( value1, Eq(123) );
    int value2 = evaluator.evaluate( "x" );
    ASSERT_THAT( value2, Eq(123) );

    int value3 = evaluator.evaluate( "var y = -456" );
    ASSERT_THAT( value3, Eq(-456) );
    int value4 = evaluator.evaluate( "y" );
    ASSERT_THAT( value4, Eq(-456) );

    int value5 = evaluator.evaluate( "x+y" );
    ASSERT_THAT( value5, Eq(123+-456) );

    int value6 = evaluator.evaluate( "z" );
    ASSERT_THAT( value6, Eq(0) );
}
