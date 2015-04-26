#include "testtoken.h"
#include "gmock/gmock.h"
#include "token.h"

using namespace testing;

TEST( TestToken, tokenIntegerCanBeCreated )
{
    TokenInteger tokInt( 123 );
    ASSERT_THAT( tokInt.type(), Eq(Token::TYPE_INTEGER) );
    ASSERT_THAT( tokInt.value(), Eq(123) );
}

TEST( TestToken, tokenVariableDeclCanBeCreated )
{
    TokenVariableDecl tokVarDec( "xyz" );
    ASSERT_THAT( tokVarDec.type(), Eq(Token::TYPE_VARIABLE_DECL) );
    ASSERT_THAT( tokVarDec.name(), StrEq("xyz") );
}

TEST( TestToken, tokenVariableRefCanBeCreated )
{
    TokenVariableRef tokVarRef( "abc" );
    ASSERT_THAT( tokVarRef.type(), Eq(Token::TYPE_VARIABLE_REF) );
    ASSERT_THAT( tokVarRef.name(), StrEq("abc") );
}

TEST( TestToken, tokenOperatorAddCanBeCreated )
{
    TokenOperatorAdd tokAdd;
    ASSERT_THAT( tokAdd.type(), Eq(Token::TYPE_OPERATOR_ADD) );
}

TEST( TestToken, tokenOperatorSubCanBeCreated )
{
    TokenOperatorSub tokSub;
    ASSERT_THAT( tokSub.type(), Eq(Token::TYPE_OPERATOR_SUB) );
}

TEST( TestToken, tokenOperatorMulCanBeCreated )
{
    TokenOperatorMul tokMul;
    ASSERT_THAT( tokMul.type(), Eq(Token::TYPE_OPERATOR_MUL) );
}

TEST( TestToken, tokenOperatorDivCanBeCreated )
{
    TokenOperatorDiv tokDiv;
    ASSERT_THAT( tokDiv.type(), Eq(Token::TYPE_OPERATOR_DIV) );
}

TEST( TestToken, tokenAssignmentCanBeCreated )
{
    TokenAssignment tokAsn;
    ASSERT_THAT( tokAsn.type(), Eq(Token::TYPE_ASSIGNMENT) );
}

TEST( TestToken, tokenParenLeftCabBeCreated )
{
    TokenParenLeft tokpl;
    ASSERT_THAT( tokpl.type(), Eq(Token::TYPE_PAREN_LEFT) );
}

TEST( TestToken, tokenParenRightCabBeCreated )
{
    TokenParenRight tokpr;
    ASSERT_THAT( tokpr.type(), Eq(Token::TYPE_PAREN_RIGHT) );
}
