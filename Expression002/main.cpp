#include "gmock/gmock.h"
#include <string.h>

using namespace testing;

extern "C" {

enum token_type {
    TOKEN_UNDEFINED,
    TOKEN_NAME,
    TOKEN_NUMBER,
    TOKEN_OP_ADD_SUB,
    TOKEN_OP_MUL_DIV,
    TOKEN_OP_EQUAL,
    TOKEN_PAREN_LEFT,
    TOKEN_PAREN_RIGHT,
    TOKEN_KEYWORD_VAR
};

static const char *source_text;
static const char *next_char;
static enum token_type current_type = TOKEN_UNDEFINED;
static char *current_string = 0;

void tokenizer_set_text( const char *text )
{
    source_text = text;
    next_char = text;
}

static bool is_digit( char c )
{
    return ('0' <= c) && (c <= '9');
}

static bool is_space( char c )
{
    static const char *space_chars = " \t\n";
    for( const char *p = space_chars; *p != '\0'; p++ ){
        if( c == *p )
            return true;
    }
    return false;
}

static bool is_alpha( char c )
{
    if( ('A' <= c) && (c <= 'Z') )
        return true;
    if( ('a' <= c) && (c <= 'z') )
        return true;
    return false;
}

static void skip_spaces()
{
    for( ; is_space(*next_char); next_char++ )
        ;
}

static void set_string( const char *startp )
{
    if( current_string != 0 )
        free( current_string );
    int size = next_char - startp;
    current_string = (char *)malloc( size + 1 );
    strncpy( current_string, startp, size );
    current_string[size] = '\0';
}

static void get_number(){
    current_type = TOKEN_NUMBER;
    const char *startp = next_char ++;
    for( ; is_digit( *next_char ); next_char ++ )
        ;
    set_string( startp );
}

static void get_single_char( enum token_type type )
{
    current_type = type;
    const char *startp = next_char ++;
    set_string( startp );
}

static bool get_name()
{
    bool ret = false;
    if( is_alpha( *next_char ) ){
        const char *startp = next_char;
        current_type = TOKEN_NAME;
        for( ; is_alpha( *next_char ); next_char ++ )
            ;
        set_string( startp );

        if( strcmp("var", current_string) == 0 ){
            current_type = TOKEN_KEYWORD_VAR;
        }
        ret = true;
    }
    return ret;
}

void tokenizer_next()
{
    skip_spaces();
    if( get_name() ){
        return;
    }
    else if( is_digit( *next_char) ){
        get_number();
    }
    else if( (*next_char == '+') || (*next_char == '-') ){
        get_single_char( TOKEN_OP_ADD_SUB );
    }
    else if( (*next_char == '*') || (*next_char == '/') ){
        get_single_char( TOKEN_OP_MUL_DIV );
    }
    else if( (*next_char == '=') ){
        get_single_char( TOKEN_OP_EQUAL );
    }
    else if( *next_char == '(' ){
        get_single_char( TOKEN_PAREN_LEFT );
    }
    else if( *next_char == ')' ){
        get_single_char( TOKEN_PAREN_RIGHT );
    }
    else{
        current_type = TOKEN_UNDEFINED;
        if( current_string != 0 )
            free( current_string );
        current_string = 0;
    }
}

enum token_type tokenizer_type()
{
    return current_type;
}

const char *tokenizer_string()
{
    return current_string;
}

enum node_type {
    NODE_UNDEFINED,
    NODE_NUMBER,
    NODE_UNARY_OP,
    NODE_BINARY_OP,
    NODE_ASSIGNMENT,
    NODE_VARIABLE
};

struct node {
    enum node_type type;
};

struct node_number {
    enum node_type type;
    int value;
};

struct node_unary_op{
    enum node_type type;
    struct node *operand;
};

struct node_binary_op{
    enum node_type type;
    char symbol;
    struct node *operand1;
    struct node *operand2;
};

struct node_assignment{
    enum node_type type;
    char *var;
    struct node *value;
};

struct node_variable{
    enum node_type type;
    char *var;
};

struct node *parse_expression();
struct node *parse_term();
struct node *parse_factor();
struct node *make_binary_op_node( char symbol, struct node *n1, struct node *n2 );
struct node *parse_assignment();

struct node *parse( const char *source )
{
    tokenizer_set_text( source );
    tokenizer_next();
    if( tokenizer_type() == TOKEN_KEYWORD_VAR ){
        return parse_assignment();
    }
    else{
        return parse_expression();
    }
}

struct node *parse_assignment()
{
    tokenizer_next();
    if( tokenizer_type() != TOKEN_NAME ){
        // Error !
        return 0;
    }
    char *var = strdup( tokenizer_string() );
    tokenizer_next();
    if( tokenizer_type() != TOKEN_OP_EQUAL ){
        // Error !
        return 0;
    }
    tokenizer_next();
    struct node *value = parse_expression();
    struct node_assignment *na = (struct node_assignment *)malloc( sizeof(struct node_assignment) );
    na->type = NODE_ASSIGNMENT;
    na->var = var;
    na->value = value;
    return (struct node *)na;
}

struct node *parse_expression()
{
    struct node *n1 = parse_term();
    if( n1 ){
        while( tokenizer_type() == TOKEN_OP_ADD_SUB ){
            char symbol = tokenizer_string()[0];
            tokenizer_next();
            struct node *n2 = parse_term();
            if( n2 == 0 ){
                // Error !
                break;
            }
            n1 = make_binary_op_node( symbol, n1, n2 );
        }
    }
    return n1;
}

struct node *parse_term()
{
    struct node *n1 = parse_factor();
    if( n1 ){
        while( tokenizer_type() == TOKEN_OP_MUL_DIV ){
            char symbol = tokenizer_string()[0];
            tokenizer_next();
            struct node *n2 = parse_factor();
            if( n2 == 0 ){
                // Error !
                break;
            }
            n1 = make_binary_op_node( symbol, n1, n2 );
        }
    }
    return n1;
}

struct node *parse_factor()
{
    struct node *n = 0;
    if( tokenizer_type() == TOKEN_NUMBER ){
        struct node_number *nn = (struct node_number *)malloc(sizeof(struct node_number));
        nn->type = NODE_NUMBER;
        nn->value = atoi(tokenizer_string());
        tokenizer_next();
        return (struct node *)nn;
    }
    else if( tokenizer_type() == TOKEN_NAME ){
        struct node_variable *nv = (struct node_variable *)malloc( sizeof(struct node_variable) );
        nv->type = NODE_VARIABLE;
        nv->var = strdup( tokenizer_string() );
        tokenizer_next();
        return (struct node *)nv;
    }
    else if( tokenizer_type() == TOKEN_PAREN_LEFT ){
        tokenizer_next();
        n = parse_expression();
        if( tokenizer_type() != TOKEN_PAREN_RIGHT ){
            // Error !
        }
        tokenizer_next();
    }
    return n;
}

struct node *make_binary_op_node( char symbol, struct node *n1, struct node *n2 )
{
    struct node_binary_op *nb = (struct node_binary_op *)malloc(sizeof(struct node_binary_op));
    nb->type = NODE_BINARY_OP;
    nb->symbol = symbol;
    nb->operand1 = n1;
    nb->operand2 = n2;
    return (struct node *)nb;
}

void var_list_add( char *key, int value );
bool var_list_get( char *key, int *value );

int evaluate( struct node *n )
{
    int value = 0;
    switch( n->type ){
    case NODE_NUMBER:
    {
        struct node_number *nn = (struct node_number *)n;
        value = nn->value;
        break;
    }
    case NODE_BINARY_OP:
    {
        struct node_binary_op *nb = (struct node_binary_op *)n;
        int o1 = evaluate( nb->operand1 );
        int o2 = evaluate( nb->operand2 );
        switch( nb->symbol ){
        case '+':
            value = o1 + o2;
            break;
        case '-':
            value = o1 - o2;
            break;
        case '*':
            value = o1 * o2;
            break;
        case '/':
            value = o1 / o2;
            break;
        default:
            break;
        }
    }
    case NODE_UNARY_OP:
        break;
    case NODE_ASSIGNMENT:
    {
        struct node_assignment *na = (struct node_assignment *)n;
        value = evaluate( na->value );
        var_list_add( na->var, value );
        break;
    }
    case NODE_VARIABLE:
    {
        struct node_variable *nv = (struct node_variable *)n;
        bool found = var_list_get( nv->var, &value );
        if( ! found ){
            // Error !
        }
        break;
    }
    default:
        break;
    }
    return value;
}

struct assoc_list {
    char *key;
    void *value;
    struct assoc_list *next;
};

static assoc_list *var_list = 0;

int var_list_count()
{
    int count = 0;
    for( struct assoc_list *acp = var_list; acp != 0; acp = acp->next, count++ )
        ;
    return count;
}

void var_list_clear()
{
    var_list = 0;
}

void var_list_add( char *key, int value )
{
    struct assoc_list *new_element = (struct assoc_list *)malloc( sizeof(struct assoc_list) );
    new_element->key = strdup( key );
    new_element->value = (int *)malloc( sizeof(int) );
    *((int*)(new_element->value)) = value;
    new_element->next = var_list;
    var_list = new_element;
}

bool var_list_get( char *key, int *value )
{
    for( struct assoc_list *acp = var_list; acp != 0; acp = acp->next ){
        if( strcmp( key, acp->key) == 0 ){
            *value = *((int *)(acp->value));
            return true;
        }
    }
    return false;
}

}

TEST( VarList, isEmptyInitially )
{
    var_list_clear();
    ASSERT_THAT( var_list_count(), Eq(0) );
}

TEST( VarList, canContainOneElement )
{
    var_list_clear();
    var_list_add( "abc", 123 );
    ASSERT_THAT( var_list_count(), Eq(1) );
    int value;
    bool found = var_list_get( "abc", &value );
    ASSERT_THAT( found, Eq(true) );
    ASSERT_THAT( value, 123 );
}

TEST( VarList, canContainManyElement )
{
    var_list_clear();
    var_list_add( "abc", 123 );
    var_list_add( "def", 456 );
    var_list_add( "ghi", 789 );

    ASSERT_THAT( var_list_count(), Eq(3) );

    int value;
    bool found = var_list_get( "abc", &value );
    ASSERT_THAT( found, Eq(true) );
    ASSERT_THAT( value, 123 );

    found = var_list_get( "def", &value );
    ASSERT_THAT( found, Eq(true) );
    ASSERT_THAT( value, 456 );

    found = var_list_get( "ghi", &value );
    ASSERT_THAT( found, Eq(true) );
    ASSERT_THAT( value, 789 );
}

TEST( VarList, returnsFalseForUnknownKey )
{
    var_list_clear();
    var_list_add( "abc", 123 );
    var_list_add( "def", 456 );
    var_list_add( "ghi", 789 );

    int value;
    bool found = var_list_get( "kjl", &value );
    ASSERT_THAT( found, Eq(false) );
}

void assert_tokenizer( const char *source, enum token_type type, const char *string )
{
    tokenizer_set_text( source );
    tokenizer_next();
    ASSERT_THAT( tokenizer_type(), Eq(type) );
    ASSERT_THAT( tokenizer_string(), StrEq(string) );
}

TEST( Tokenizer, recognizesSingleDigitAsNumber )
{
    assert_tokenizer( "1", TOKEN_NUMBER, "1" );
}

TEST( Tokenizer, recognizesMultipleDigitsAsNumber )
{
    assert_tokenizer( "1234567890", TOKEN_NUMBER, "1234567890" );
}

TEST( Tokenizer, skipsSpaceCharacters )
{
    assert_tokenizer( " \t \n 12345", TOKEN_NUMBER, "12345" );
}

TEST( Tokenizer, recognizesOperatorAdd )
{
    assert_tokenizer( "+", TOKEN_OP_ADD_SUB, "+" );
}

TEST( Tokenizer, recognizesOperatorSub )
{
    assert_tokenizer( "-", TOKEN_OP_ADD_SUB, "-" );
}

TEST( Tokenizer, recognizesOperatorMul )
{
    assert_tokenizer( "*", TOKEN_OP_MUL_DIV, "*" );
}

TEST( Tokenizer, recognizesOperatorDiv )
{
    assert_tokenizer( "/", TOKEN_OP_MUL_DIV, "/" );
}

TEST( Tokenizer, recognizesParenthesisLeft )
{
    assert_tokenizer( "(", TOKEN_PAREN_LEFT, "(" );
}

TEST( Tokenizer, recognizesParenthesisRight )
{
    assert_tokenizer( ")", TOKEN_PAREN_RIGHT, ")" );
}

TEST( Tokenizer, recognizesMultipleTokes )
{
    tokenizer_set_text( "123+45*(6789-98)/7654" );
    tokenizer_next();
    ASSERT_THAT( tokenizer_type(), Eq(TOKEN_NUMBER) );
    ASSERT_THAT( tokenizer_string(), StrEq("123") );
    tokenizer_next();
    ASSERT_THAT( tokenizer_type(), Eq(TOKEN_OP_ADD_SUB) );
    ASSERT_THAT( tokenizer_string(), StrEq("+") );
    tokenizer_next();
    ASSERT_THAT( tokenizer_type(), Eq(TOKEN_NUMBER) );
    ASSERT_THAT( tokenizer_string(), StrEq("45") );
    tokenizer_next();
    ASSERT_THAT( tokenizer_type(), Eq(TOKEN_OP_MUL_DIV) );
    ASSERT_THAT( tokenizer_string(), StrEq("*") );
    tokenizer_next();
    ASSERT_THAT( tokenizer_type(), Eq(TOKEN_PAREN_LEFT) );
    ASSERT_THAT( tokenizer_string(), StrEq("(") );
    tokenizer_next();
    ASSERT_THAT( tokenizer_type(), Eq(TOKEN_NUMBER) );
    ASSERT_THAT( tokenizer_string(), StrEq("6789") );
    tokenizer_next();
    ASSERT_THAT( tokenizer_type(), Eq(TOKEN_OP_ADD_SUB) );
    ASSERT_THAT( tokenizer_string(), StrEq("-") );
    tokenizer_next();
    ASSERT_THAT( tokenizer_type(), Eq(TOKEN_NUMBER) );
    ASSERT_THAT( tokenizer_string(), StrEq("98") );
    tokenizer_next();
    ASSERT_THAT( tokenizer_type(), Eq(TOKEN_PAREN_RIGHT) );
    ASSERT_THAT( tokenizer_string(), StrEq(")") );
    tokenizer_next();
    ASSERT_THAT( tokenizer_type(), Eq(TOKEN_OP_MUL_DIV) );
    ASSERT_THAT( tokenizer_string(), StrEq("/") );
    tokenizer_next();
    ASSERT_THAT( tokenizer_type(), Eq(TOKEN_NUMBER) );
    ASSERT_THAT( tokenizer_string(), StrEq("7654") );
    tokenizer_next();
    ASSERT_THAT( tokenizer_type(), Eq(TOKEN_UNDEFINED) );
    ASSERT_THAT( tokenizer_string(), Eq((const char *)0) );
}

TEST( Tokenizer, recognizesAssignment )
{
    tokenizer_set_text( "var abc = 123");
    tokenizer_next();
    ASSERT_THAT( tokenizer_type(), Eq(TOKEN_KEYWORD_VAR) );
    ASSERT_THAT( tokenizer_string(), StrEq("var"));
    tokenizer_next();
    ASSERT_THAT( tokenizer_type(), Eq(TOKEN_NAME) );
    ASSERT_THAT( tokenizer_string(), StrEq("abc"));
    tokenizer_next();
    ASSERT_THAT( tokenizer_type(), Eq(TOKEN_OP_EQUAL) );
    ASSERT_THAT( tokenizer_string(), StrEq("="));
    tokenizer_next();
    ASSERT_THAT( tokenizer_type(), Eq(TOKEN_NUMBER) );
    ASSERT_THAT( tokenizer_string(), StrEq("123"));
}

TEST( Parser, recognizesNumber )
{
    struct node *n = parse( "123" );
    ASSERT_THAT( n->type, Eq(NODE_NUMBER) );
    struct node_number *nn = (struct node_number *)n;
    ASSERT_THAT(nn->value, Eq(123));
}

void assert_number_node( struct node *n, int value )
{
    ASSERT_THAT( n->type, Eq(NODE_NUMBER) );
    struct node_number *nn = (struct node_number *)n;
    ASSERT_THAT( nn->value, value );
}

TEST( Parser, recognizesMultiply )
{
    struct node *n = parse( "123*456/789" );
    ASSERT_THAT( n->type, Eq(NODE_BINARY_OP) );
    struct node_binary_op *nb = (struct node_binary_op *)n;
    ASSERT_THAT( nb->symbol, Eq('/') );
//    assert_number_node( nb->operand1, 123 );
//    assert_number_node( nb->operand2, 456 );
    assert_number_node( nb->operand2, 789 );
}

TEST( Parser, recognizesAssignment )
{
    struct node *n = parse( "var abc = 123" );
    ASSERT_THAT( n, Ne(static_cast<struct node *>(0)) );
    ASSERT_THAT( n->type, Eq(NODE_ASSIGNMENT) );
    struct node_assignment *na = (struct node_assignment *)n;
    ASSERT_THAT( na->var, StrEq("abc") );
    ASSERT_THAT( na->value->type, Eq(NODE_NUMBER) );
    struct node_number *nn = (struct node_number *)na->value;
    ASSERT_THAT( nn->value, Eq(123) );
}

TEST( Evaluater, evluateNumber )
{
    struct node *n = parse( "123" );
    ASSERT_THAT( evaluate(n), Eq(123) );
}

TEST( Evaluater, evaluateAddition )
{
    struct node *n = parse( "123+456" );
    ASSERT_THAT( evaluate(n), Eq(123+456) );
}

TEST( Evaluater, evaluateSubtraction )
{
    struct node *n = parse( "123-456" );
    ASSERT_THAT( evaluate(n), Eq(123-456) );
}

TEST( Evaluater, evaluateMultiplication )
{
    struct node *n = parse( "123*456" );
    ASSERT_THAT( evaluate(n), Eq(123*456) );
}

TEST( Evaluater, evaluateDivision )
{
    struct node *n = parse( "1234/56" );
    ASSERT_THAT( evaluate(n), Eq(1234/56) );
}

TEST( Evaluater, evaluateLongExpression )
{
    struct node *n = parse( "12+34*56-78/9" );
    ASSERT_THAT( evaluate(n), Eq(12+34*56-78/9) );
}

TEST( Evaluater, evaluateLongExpressionWithParenthesis )
{
    struct node *n = parse( "(12+34)*(56-78)/9" );
    ASSERT_THAT( evaluate(n), Eq((12+34)*(56-78)/9) );
}

TEST( Evaluater, evaluateAssignemt )
{
    struct node *n = parse( "var abc = 123" );
    ASSERT_THAT( evaluate(n), Eq(123) );
    n = parse( "var def = 2 * abc" );
    ASSERT_THAT( evaluate(n), Eq(2*123) );
    n = parse( "var ghi = abc - def" );
    ASSERT_THAT( evaluate(n), Eq(123-(2*123)) );
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleMock(&argc,argv);
    return RUN_ALL_TESTS();
}
