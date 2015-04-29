#include "testtokenizer.h"
#include "tokenizer.h"

TEST_F( TestTokenizer, tokenizerRecognizesSingleDigit0AsInteger )
{
    tokenizer.setSource( "0" );
    Token *token = tokenizer.next();
    ASSERT_THAT( token->type(), Eq(Token::TYPE_INTEGER) );
    TokenInteger *tokenInt = dynamic_cast<TokenInteger *>(token);
    ASSERT_THAT( tokenInt->value(), Eq(0) );
}

TEST_F( TestTokenizer, tokenizerRecognizesSingleDigit9AsInteger )
{
    tokenizer.setSource( "9" );
    Token *token = tokenizer.next();
    ASSERT_THAT( token->type(), Eq(Token::TYPE_INTEGER) );
    TokenInteger *tokenInt = dynamic_cast<TokenInteger *>(token);
    ASSERT_THAT( tokenInt->value(), Eq(9) );
}

TEST_F( TestTokenizer, tokenizerRecognizesMultiDigitsAsInteger )
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

TEST_F( TestTokenizer, tokenizerRecognizesSingleAlphabetAsName )
{
    tokenizer.setSource( "A" );
    Token *token = tokenizer.next();
    ASSERT_THAT( token->type(), Eq(Token::TYPE_NAME) );
    TokenName *tokenName = dynamic_cast<TokenName *>(token);
    ASSERT_THAT( tokenName->name(), StrEq("A") );
}

TEST_F( TestTokenizer, tokenizerRecognizesMultipleAlphabetsAsName )
{
    tokenizer.setSource( "AZaz09" );
    Token *token = tokenizer.next();
    ASSERT_THAT( token->type(), Eq(Token::TYPE_NAME) );
    TokenName *tokenName = dynamic_cast<TokenName *>(token);
    ASSERT_THAT( tokenName->name(), StrEq("AZaz09") );
}

TEST_F( TestTokenizer, tokenizerRecognizesPlusSignAsOperator )
{
    tokenizer.setSource( "+" );
    Token *token = tokenizer.next();
    ASSERT_THAT( token->type(), Eq(Token::TYPE_OPERATOR_ADD) );
}

TEST_F( TestTokenizer, tokenizerRecognizesMinusSignAsOperator )
{
    tokenizer.setSource( "-" );
    Token *token = tokenizer.next();
    ASSERT_THAT( token->type(), Eq(Token::TYPE_OPERATOR_SUB) );
}

TEST_F( TestTokenizer, tokenizerRecognizesAsteriskAsOperator )
{
    tokenizer.setSource( "*" );
    Token *token = tokenizer.next();
    ASSERT_THAT( token->type(), Eq(Token::TYPE_OPERATOR_MUL) );
}

TEST_F( TestTokenizer, tokenizerRecognizesSlashSignAsOperator )
{
    tokenizer.setSource( "/" );
    Token *token = tokenizer.next();
    ASSERT_THAT( token->type(), Eq(Token::TYPE_OPERATOR_DIV) );
}

TEST_F( TestTokenizer, tokenizerRecognizesEqualSignAsAssignment )
{
    tokenizer.setSource( "=" );
    Token *token = tokenizer.next();
    ASSERT_THAT( token->type(), Eq(Token::TYPE_ASSIGNMENT) );
}

TEST_F( TestTokenizer, tokenizerRecognizesOpenParenthesis )
{
    tokenizer.setSource( "(" );
    Token *token = tokenizer.next();
    ASSERT_THAT( token->type(), Eq(Token::TYPE_PAREN_OPEN) );
}

TEST_F( TestTokenizer, tokenizerRecognizesCloseParenthesis )
{
    tokenizer.setSource( ")" );
    Token *token = tokenizer.next();
    ASSERT_THAT( token->type(), Eq(Token::TYPE_PAREN_CLOSE) );
}

TEST_F( TestTokenizer, tokenizerRecognizesMultipleTokens )
{
    tokenizer.setSource( "xyz=123+(456-abc)*def/789");
    Token *token = tokenizer.next();
    ASSERT_THAT( token->type(), Eq(Token::TYPE_NAME) );
    token = tokenizer.next();
    ASSERT_THAT( token->type(), Eq(Token::TYPE_ASSIGNMENT) );
    token = tokenizer.next();
    ASSERT_THAT( token->type(), Eq(Token::TYPE_INTEGER) );
    token = tokenizer.next();
    ASSERT_THAT( token->type(), Eq(Token::TYPE_OPERATOR_ADD) );
    token = tokenizer.next();
    ASSERT_THAT( token->type(), Eq(Token::TYPE_PAREN_OPEN) );
    token = tokenizer.next();
    ASSERT_THAT( token->type(), Eq(Token::TYPE_INTEGER) );
    token = tokenizer.next();
    ASSERT_THAT( token->type(), Eq(Token::TYPE_OPERATOR_SUB) );
    token = tokenizer.next();
    ASSERT_THAT( token->type(), Eq(Token::TYPE_NAME) );
    token = tokenizer.next();
    ASSERT_THAT( token->type(), Eq(Token::TYPE_PAREN_CLOSE) );
    token = tokenizer.next();
    ASSERT_THAT( token->type(), Eq(Token::TYPE_OPERATOR_MUL) );
    token = tokenizer.next();
    ASSERT_THAT( token->type(), Eq(Token::TYPE_NAME) );
    token = tokenizer.next();
    ASSERT_THAT( token->type(), Eq(Token::TYPE_OPERATOR_DIV) );
    token = tokenizer.next();
    ASSERT_THAT( token->type(), Eq(Token::TYPE_INTEGER) );
    token = tokenizer.next();
    ASSERT_THAT( token->type(), Eq(Token::TYPE_END) );
}

TEST_F( TestTokenizer, tokenizerRecognizesKeywordVar )
{
    tokenizer.setSource( "var" );
    Token *token = tokenizer.next();
    ASSERT_THAT( token->type(), Eq(Token::TYPE_KEYWORD_VAR) );
}
