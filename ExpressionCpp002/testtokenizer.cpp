#include "testtokenizer.h"
#include "tokenizer.h"

TEST_F( TestTokenizer, tokenizerRecignizesSingleDigit0AsInteger )
{
    tokenizer.setSource( "0" );
    Token *token = tokenizer.next();
    ASSERT_THAT( token->type(), Eq(Token::TYPE_INTEGER) );
    TokenInteger *tokenInt = dynamic_cast<TokenInteger *>(token);
    ASSERT_THAT( tokenInt->value(), Eq(0) );
}

TEST_F( TestTokenizer, tokenizerRecignizesSingleDigit9AsInteger )
{
    tokenizer.setSource( "9" );
    Token *token = tokenizer.next();
    ASSERT_THAT( token->type(), Eq(Token::TYPE_INTEGER) );
    TokenInteger *tokenInt = dynamic_cast<TokenInteger *>(token);
    ASSERT_THAT( tokenInt->value(), Eq(9) );
}

TEST_F( TestTokenizer, tokenizerRecignizesMultiDigitAsInteger )
{
    tokenizer.setSource( "190" );
    Token *token = tokenizer.next();
    ASSERT_THAT( token->type(), Eq(Token::TYPE_INTEGER) );
    TokenInteger *tokenInt = dynamic_cast<TokenInteger *>(token);
    ASSERT_THAT( tokenInt->value(), Eq(190) );
}

TEST_F( TestTokenizer, tokenizerSkipsSpaceCharatcers )
{
    tokenizer.setSource( " \n \t 190" );
    Token *token = tokenizer.next();
    ASSERT_THAT( token->type(), Eq(Token::TYPE_INTEGER) );
    TokenInteger *tokenInt = dynamic_cast<TokenInteger *>(token);
    ASSERT_THAT( tokenInt->value(), Eq(190) );
}
