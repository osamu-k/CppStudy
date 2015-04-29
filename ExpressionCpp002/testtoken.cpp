#include "testtoken.h"
#include "gmock/gmock.h"
#include "token.h"

using namespace testing;

TEST( TestToken, tokenCanBeCreated )
{
    Token token;
    ASSERT_THAT( token.type(), Eq(Token::TYPE_UNDEFINED) );
}

TEST( TestToken, typedTokenCanBeCreated )
{
    Token token( Token::TYPE_OPERATOR_ADD );
    ASSERT_THAT( token.type(), Eq(Token::TYPE_OPERATOR_ADD) );
}

TEST( TestToken, tokenIntegerCanBeCreated )
{
    TokenInteger tokInt( 123 );
    ASSERT_THAT( tokInt.type(), Eq(Token::TYPE_INTEGER) );
    ASSERT_THAT( tokInt.value(), Eq(123) );
}

TEST( TestToken, tokenNameCanBeCreated )
{
    TokenName tokVar( "xyz" );
    ASSERT_THAT( tokVar.type(), Eq(Token::TYPE_NAME) );
    ASSERT_THAT( tokVar.name(), StrEq("xyz") );
}
