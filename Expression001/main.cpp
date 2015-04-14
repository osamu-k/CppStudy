#include "gmock/gmock.h"

using namespace testing;

extern "C" {

enum token_type {
    TOKEN_TYPE_UNDEFINED,
    TOKEN_TYPE_NUMBER,
    TOKEN_TYPE_OP_ADD_SUB,
    TOKEN_TYPE_OP_MUL_DIV,
    TOKEN_TYPE_PAREN_LEFT,
    TOKEN_TYPE_PAREN_RIGHT
};

struct token {
    enum token_type type;
};

struct token_number {
    enum token_type type;
    int value;
};

struct token_operator {
    enum token_type type;
    char symbol;
};

enum expression_type {
    EXPR_TYPE_UNDEFINED,
    EXPR_TYPE_NUMBER,
    EXPR_TYPE_OPERATOR
};

struct expression {
    enum expression_type type;
};

struct expr_number {
    enum expression_type type;
    int value;
};

struct expr_operator {
    enum expression_type type;
    char symbol;
    expression *left;
    expression *right;
};

void skip_spaces( const char **text ){
    for( ; (**text == ' ') || (**text == '\t') || (**text == '\n'); (*text)++ )
        ;
}

bool is_digit( const char c )
{
    return ('0' <= c) && (c <= '9');
}

struct token *next_token( const char **text )
{
    skip_spaces( text );
    if( is_digit(**text) ){
        int value = **text - '0';
        for( (*text)++; is_digit(**text); (*text)++ ){
            value *= 10;
            value += (**text - '0');
        }
        struct token_number *tok = (struct token_number *)malloc( sizeof(struct token_number) );
        tok->type = TOKEN_TYPE_NUMBER;
        tok->value = value;
        return (struct token *)tok;
    }
    else if( (**text == '+') || (**text == '-') ){
        struct token_operator *tok = (struct token_operator *)malloc( sizeof(struct token_operator) );
        tok->type = TOKEN_TYPE_OP_ADD_SUB;
        tok->symbol = **text;
        (*text)++;
        return (struct token *)tok;
    }
    else if( (**text == '*') || (**text == '/') ){
        struct token_operator *tok = (struct token_operator *)malloc( sizeof(struct token_operator) );
        tok->type = TOKEN_TYPE_OP_MUL_DIV;
        tok->symbol = **text;
        (*text)++;
        return (struct token *)tok;
    }
    else if( **text == '(' ){
        struct token *tok = (struct token *)malloc( sizeof(struct token) );
        tok->type = TOKEN_TYPE_PAREN_LEFT;
        (*text)++;
        return tok;
    }
    else if( **text == ')' ){
        struct token *tok = (struct token *)malloc( sizeof(struct token) );
        tok->type = TOKEN_TYPE_PAREN_RIGHT;
        (*text)++;
        return tok;
    }
    return 0;
}

struct expression *parse_expression( struct token **token, const char **text );
struct expression *parse_term( struct token **token, const char **text );
struct expression *parse_factor( struct token **token, const char **text );


struct expression *parse( const char *text )
{
    struct token *token = next_token( &text );
    return parse_expression( &token, &text);
}

struct expression *parse_expression( struct token **token, const char **text )
{
    struct expression *e1 = parse_term( token, text );
    if( e1 == 0 )
        return e1;
    while( ((*token) != 0) && ((*token)->type == TOKEN_TYPE_OP_ADD_SUB) ){
        char symbol = ((struct token_operator *)(*token))->symbol;
        (*token) = next_token( text );
        struct expression *e2 = parse_term( token, text );
        if( e2 == 0 ){
            // Error !
            return e1;
        }
        struct expr_operator *exp = (struct expr_operator *)malloc( sizeof(struct expr_operator) );
        exp->type = EXPR_TYPE_OPERATOR;
        exp->symbol = symbol;
        exp->left = e1;
        exp->right = e2;
        e1 = (struct expression *)exp;
    }
    return e1;
}

struct expression *parse_term( struct token **token, const char **text )
{
    struct expression *e1 = parse_factor( token, text );
    if( e1 == 0 )
        return e1;
    while( ((*token) != 0) && ((*token)->type == TOKEN_TYPE_OP_MUL_DIV) ){
        char symbol = ((struct token_operator *)(*token))->symbol;
        (*token) = next_token( text );
        struct expression *e2 = parse_factor( token, text );
        if( e2 == 0 ){
            // Error !
            return e1;
        }
        struct expr_operator *exp = (struct expr_operator *)malloc( sizeof(struct expr_operator) );
        exp->type = EXPR_TYPE_OPERATOR;
        exp->symbol = symbol;
        exp->left = e1;
        exp->right = e2;
        e1 = (struct expression *)exp;
    }
    return e1;
}

struct expression *parse_factor( struct token **token, const char **text )
{
    if( token == 0 )
        return 0;

    if( (*token)->type == TOKEN_TYPE_NUMBER ){
        int value = ((struct expr_number *)(*token))->value;
        *token = next_token( text );
        struct expr_number *exp = (struct expr_number *)malloc( sizeof(struct expr_number) );
        exp->type = EXPR_TYPE_NUMBER;
        exp->value = value;
        return (struct expression *)exp;
    }
    if( (*token)->type == TOKEN_TYPE_PAREN_LEFT ){
        *token = next_token( text );
        struct expression *exp = parse_expression( token, text );
        if( ((*token) != 0) && ((*token)->type == TOKEN_TYPE_PAREN_RIGHT) ){
            *token = next_token( text );
            return exp;
        }
        // Error !
        return exp;
    }
    // Error !
    return 0;
}

int eval( struct expression *exp )
{
    if( exp->type == EXPR_TYPE_NUMBER ){
        printf( "number = %d\n", ((struct expr_number *)exp)->value );
        return ((struct expr_number *)exp)->value;
    }
    else if( exp->type == EXPR_TYPE_OPERATOR ){
        struct expr_operator *expo = (struct expr_operator *)exp;
        int left = eval(expo->left);
        int right = eval(expo->right);
        int value = 0;
        switch(expo->symbol){
        case '+':
            value = left + right;
            break;
        case '-':
            value = left - right;
            break;
        case '*':
            value = left * right;
            break;
        case '/':
            value = left / right;
            break;
        }
        printf( "%d %c %d = %d\n", left, expo->symbol, right, value );
        return value;
    }
    // Error !
    return 0;
}

/*

<expression> ::= <term>{ <opeas> <term> }
<term> ::= <factor>{ <opemd> <factor> }
<factor> ::= <number>|( <expression> )
<number> ::= <digit>{<digit>}
<opeas> ::= + | -
<opemd> ::= * | /
<digit> ::= 0|1|2|3|4|5|6|7|8|9

*/

}

TEST( Tokenizer, recognizesIntegerAsAToken )
{
    const char *text = "1";

    token *token = next_token( &text );
    ASSERT_THAT( token->type, Eq(TOKEN_TYPE_NUMBER) );
}

TEST( Tokenizer, recognizesInteger1 )
{
    const char *text = "1";

    struct token *token = next_token( &text );
    ASSERT_THAT( token->type, Eq(TOKEN_TYPE_NUMBER) );
    ASSERT_THAT( ((struct token_number *)token)->value, Eq(1) );
}

TEST( Tokenizer, recognizesInteger3 )
{
    const char *text = "3";

    token *token = next_token( &text );
    ASSERT_THAT( token->type, Eq(TOKEN_TYPE_NUMBER) );
    ASSERT_THAT( ((struct token_number *)token)->value, Eq(3) );
}

TEST( Tokenizer, recognizesMultiDigitsInteger )
{
    const char *text = "123";

    token *token = next_token( &text );
    ASSERT_THAT( token->type, Eq(TOKEN_TYPE_NUMBER) );
    ASSERT_THAT( ((struct token_number *)token)->value, Eq(123) );
}

TEST( Tokenizer, skipsSpaceCharacters )
{
    const char *text = " \t \n 123";

    token *token = next_token( &text );
    ASSERT_THAT( token->type, Eq(TOKEN_TYPE_NUMBER) );
    ASSERT_THAT( ((struct token_number *)token)->value, Eq(123) );
}

TEST( Tokenizer, recognizesPlusOperator )
{
    const char *text = "+";
    token *token = next_token( &text );
    ASSERT_THAT( token->type, Eq(TOKEN_TYPE_OP_ADD_SUB) );
    ASSERT_THAT( ((struct token_operator *)token)->symbol, Eq('+') );
}

TEST( Tokenizer, recognizesMinusOperator )
{
    const char *text = "-";
    token *token = next_token( &text );
    ASSERT_THAT( token->type, Eq(TOKEN_TYPE_OP_ADD_SUB) );
    ASSERT_THAT( ((struct token_operator *)token)->symbol, Eq('-') );
}

TEST( Tokenizer, recognizesAsteriskOperator )
{
    const char *text = "*";
    token *token = next_token( &text );
    ASSERT_THAT( token->type, Eq(TOKEN_TYPE_OP_MUL_DIV) );
    ASSERT_THAT( ((struct token_operator *)token)->symbol, Eq('*') );
}

TEST( Tokenizer, recognizesSlashOperator )
{
    const char *text = "/";
    token *token = next_token( &text );
    ASSERT_THAT( token->type, Eq(TOKEN_TYPE_OP_MUL_DIV) );
    ASSERT_THAT( ((struct token_operator *)token)->symbol, Eq('/') );
}

TEST( Tokenizer, recognizesOpenParenthesis )
{
    const char *text = "(";
    token *token = next_token( &text );
    ASSERT_THAT( token->type, Eq(TOKEN_TYPE_PAREN_LEFT) );
}

TEST( Tokenizer, recognizesCloseParenthesis )
{
    const char *text = ")";
    token *token = next_token( &text );
    ASSERT_THAT( token->type, Eq(TOKEN_TYPE_PAREN_RIGHT) );
}

TEST( Tokenizer, recognizesMultipleTokes )
{
    const char *text = " 123 + -456 - 789 * -987 / 654";

    token *token = next_token( &text );
    ASSERT_THAT( token->type, Eq(TOKEN_TYPE_NUMBER) );
    ASSERT_THAT( ((struct token_number *)token)->value, Eq(123) );

    token = next_token( &text );
    ASSERT_THAT( token->type, Eq(TOKEN_TYPE_OP_ADD_SUB) );
    ASSERT_THAT( ((struct token_operator *)token)->symbol, Eq('+') );

    token = next_token( &text );
    ASSERT_THAT( token->type, Eq(TOKEN_TYPE_OP_ADD_SUB) );
    ASSERT_THAT( ((struct token_operator *)token)->symbol, Eq('-') );

    token = next_token( &text );
    ASSERT_THAT( token->type, Eq(TOKEN_TYPE_NUMBER) );
    ASSERT_THAT( ((struct token_number *)token)->value, Eq(456) );

    token = next_token( &text );
    ASSERT_THAT( token->type, Eq(TOKEN_TYPE_OP_ADD_SUB) );
    ASSERT_THAT( ((struct token_operator *)token)->symbol, Eq('-') );

    token = next_token( &text );
    ASSERT_THAT( token->type, Eq(TOKEN_TYPE_NUMBER) );
    ASSERT_THAT( ((struct token_number *)token)->value, Eq(789) );

    token = next_token( &text );
    ASSERT_THAT( token->type, Eq(TOKEN_TYPE_OP_MUL_DIV) );
    ASSERT_THAT( ((struct token_operator *)token)->symbol, Eq('*') );

    token = next_token( &text );
    ASSERT_THAT( token->type, Eq(TOKEN_TYPE_OP_ADD_SUB) );
    ASSERT_THAT( ((struct token_operator *)token)->symbol, Eq('-') );

    token = next_token( &text );
    ASSERT_THAT( token->type, Eq(TOKEN_TYPE_NUMBER) );
    ASSERT_THAT( ((struct token_number *)token)->value, Eq(987) );

    token = next_token( &text );
    ASSERT_THAT( token->type, Eq(TOKEN_TYPE_OP_MUL_DIV) );
    ASSERT_THAT( ((struct token_operator *)token)->symbol, Eq('/') );

    token = next_token( &text );
    ASSERT_THAT( token->type, Eq(TOKEN_TYPE_NUMBER) );
    ASSERT_THAT( ((struct token_number *)token)->value, Eq(654) );
}

TEST( Parser, recognizesInteger )
{
    const char *text = " 123 ";
    struct expression *expression = parse( text );
    ASSERT_THAT( expression, Ne( reinterpret_cast<struct expression *>(0) ) );
    ASSERT_THAT( expression->type, Eq( EXPR_TYPE_NUMBER ) );

    expr_number *expi = reinterpret_cast<expr_number *>(expression);
    ASSERT_THAT( expi->value, Eq(123) );
    ASSERT_THAT( eval(expression), Eq(123) );
}

TEST( Parser, recognizesMultiply )
{
    const char *text = " 123 * 456";
    struct expression *expression = parse( text );
    ASSERT_THAT( expression->type, Eq( EXPR_TYPE_OPERATOR ) );

    expr_operator *expi = reinterpret_cast<expr_operator *>(expression);
    ASSERT_THAT( expi->symbol, Eq('*') );
    ASSERT_THAT( eval(expression), Eq(123 * 456) );
}

TEST( Parser, recognizesExpression1 )
{
    const char *text = "12 + 34 * 56 - 78";
    struct expression *expression = parse( text );
    ASSERT_THAT( eval(expression), Eq(12 + 34 * 56 - 78) );
}

TEST( Parser, recognizesExpression2 )
{
    const char *text = "(12 + 34) * (56 - 78)";
    struct expression *expression = parse( text );
    ASSERT_THAT( eval(expression), Eq((12 + 34) * (56 - 78)) );
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleMock(&argc,argv);
    return RUN_ALL_TESTS();
}

