#include "gmock/gmock.h"

#include <ctype.h>
#include <string.h>

using namespace std;
using namespace testing;

class Token
{
public:
    enum Type {
        TYPE_UNDEFINED,
        TYPE_INTEGER,
        TYPE_NAME,
        TYPE_OP_ADD_SUB,
        TYPE_OP_MUL_DIV,
        TYPE_PAREN_LEFT,
        TYPE_PAREN_RIGHT,
        TYPE_EQUAL,
        TYPE_KEY_VAR,
        TYPE_END
    };

    Token( Type type = TYPE_UNDEFINED, string text = string() )
        : m_type(type),m_text(text)
    {
    }

    Token( Type type, char c )
        : m_type(type),m_text( string(1,c))
    {
    }

    ~Token()
    {
    }

    Token::Type type()
    {
        return m_type;
    }

    string text()
    {
        return m_text;
    }

private:
    Type m_type;
    string m_text;
};

class Tokenizer
{
public:
    Tokenizer()
    {
    }

    ~Tokenizer()
    {
    }

    void setSource( const string &source )
    {
        m_source = source;
        m_sourceIt = m_source.begin();
    }

    Token next();

private:
    void skipSpace();
    Token makeInteger();
    Token makeName();
    Token makeOperator();
    string m_source;
    string::iterator m_sourceIt;
};

Token Tokenizer::next()
{
    skipSpace();
    Token token;

    if( m_sourceIt == m_source.end() )
        return Token( Token::TYPE_END );

    token = makeInteger();
    if( token.type() != Token::TYPE_UNDEFINED )
        return token;

    token = makeName();
    if( token.type() != Token::TYPE_UNDEFINED )
        return token;

    token = makeOperator();
    if( token.type() != Token::TYPE_UNDEFINED )
        return token;

    return Token( Token::TYPE_UNDEFINED );
}

void Tokenizer::skipSpace()
{
    while( (m_sourceIt != m_source.end()) && isspace(*(m_sourceIt)) )
        m_sourceIt++;
}

Token Tokenizer::makeInteger()
{
    if( (m_sourceIt != m_source.end()) && isnumber(*m_sourceIt) ){
        string text;
        text += *(m_sourceIt++);
        while( (m_sourceIt != m_source.end()) && isnumber(*m_sourceIt) ){
            text += *(m_sourceIt++);
        }
        return Token( Token::TYPE_INTEGER, text );
    }
    else{
        return Token();
    }
}

Token Tokenizer::makeName()
{
    if( (m_sourceIt != m_source.end()) && isalpha(*m_sourceIt) ){
        string text;
        text += *(m_sourceIt)++;
        while( (m_sourceIt != m_source.end()) && isalnum(*m_sourceIt) ){
            text += *(m_sourceIt++);
        }
        if( text == "var" )
            return Token(Token::TYPE_KEY_VAR, text );
        else
            return Token( Token::TYPE_NAME, text );
    }
    else{
        return Token();
    }
}

Token Tokenizer::makeOperator()
{
    if( m_sourceIt != m_source.end() ){
        Token::Type type;
        switch(*m_sourceIt){
        case '+':
        case '-':
            return Token( Token::TYPE_OP_ADD_SUB, *(m_sourceIt++) );
        case '*':
        case '/':
            return Token( Token::TYPE_OP_MUL_DIV, *(m_sourceIt++) );
        case '=':
            return Token( Token::TYPE_EQUAL, *(m_sourceIt++) );
        case '(':
            return Token( Token::TYPE_PAREN_LEFT, *(m_sourceIt++) );
        case ')':
            return Token( Token::TYPE_PAREN_RIGHT, *(m_sourceIt++) );
        }
    }
    return Token();
}

class Node
{
public:
    enum Type{
        TYPE_UNDEFINED,
        TYPE_INTEGER,
        TYPE_VARIABLE,
        TYPE_ADD,
        TYPE_SUB,
        TYPE_MUL,
        TYPE_DIV,
        TYPE_ASSIGN
    };
    Node( Type type = TYPE_UNDEFINED )
        : m_type(type)
    {
    }
    virtual ~Node()
    {
    }
    Type type()
    {
        return m_type;
    }

private:
    Type m_type;
};

class NodeInteger : public Node
{
public:
    NodeInteger( long value = 0 )
        :Node( Node::TYPE_INTEGER ), m_value(value)
    {
    }

    virtual ~NodeInteger()
    {
    }

    long value()
    {
        return m_value;
    }

private:
    long m_value;
};

class NodeVariable : public Node
{
public:
    NodeVariable( string name = string() )
        :Node( Node::TYPE_VARIABLE ), m_name(name)
    {
    }

    virtual ~NodeVariable()
    {
    }

    string name()
    {
        return m_name;
    }

private:
    string m_name;
};

class NodeBinary : public Node
{
public:
    NodeBinary( Node::Type type,  Node *left, Node *right )
        : Node(type), m_left( left ), m_right( right )
    {
    }

    ~NodeBinary()
    {
    }

    Node *left()
    {
        return m_left;
    }

    Node *right()
    {
        return m_right;
    }

private:
    Node *m_left;
    Node *m_right;
};

class NodeAdd : public NodeBinary
{
public:
    NodeAdd( Node *left, Node *right )
        :NodeBinary( Node::TYPE_ADD, left, right )
    {
    }

    ~NodeAdd()
    {
    }
};

class NodeSub : public NodeBinary
{
public:
    NodeSub( Node *left, Node *right )
        :NodeBinary( Node::TYPE_SUB, left, right )
    {
    }

    ~NodeSub()
    {
    }
};

class NodeMul : public NodeBinary
{
public:
    NodeMul( Node *left, Node *right )
        :NodeBinary( Node::TYPE_MUL, left, right )
    {
    }

    ~NodeMul()
    {
    }
};

class NodeDiv : public NodeBinary
{
public:
    NodeDiv( Node *left, Node *right )
        :NodeBinary( Node::TYPE_DIV, left, right )
    {
    }

    ~NodeDiv()
    {
    }
};

class NodeAssign : public Node
{
public:
    NodeAssign( NodeVariable *var, Node *value )
        : m_variable( var ), m_value( value )
    {
    }

    ~NodeAssign()
    {
    }

    NodeVariable *variable()
    {
        return m_variable;
    }

    Node *value()
    {
        return m_value;
    }

private:
    NodeVariable *m_variable;
    Node *m_value;
};

class Parser{
public:
    Parser( Tokenizer *tokenizer )
        : m_tokenizer(tokenizer)
    {
    }
    ~Parser()
    {
    }

    void setSource( string source )
    {
        m_tokenizer->setSource( source );
        m_token = m_tokenizer->next();
    }

    Node *parse();
    Node *parseAssignment();
    Node *parseExpression();
    Node *parseTerm();
    Node *parseFactor();

private:
    Tokenizer *m_tokenizer;
    Token m_token;
};

Node *Parser::parse()
{
    if( m_token.type() == Token::TYPE_KEY_VAR ){
        m_token = m_tokenizer->next();
        return parseAssignment();
    }
    else{
        return parseExpression();
    }
}

Node *Parser::parseAssignment()
{
    if( m_token.type() != Token::TYPE_NAME ){
        // Error !
        return 0;
    }
    NodeVariable *var = new NodeVariable( m_token.text() );
    m_tokenizer->next();
    if( m_token.type() != Token::TYPE_EQUAL ){
        // Error !
        return 0;
    }
    m_token = m_tokenizer->next();
    Node *value = parseExpression();
    NodeAssign *na = new NodeAssign( var, value );
    return na;
}

Node *Parser::parseExpression()
{
    Node *n1 = parseTerm();
    if( n1 ){
        while( m_token.type() == Token::TYPE_OP_ADD_SUB ){
            string token_text = m_token.text();
            m_token = m_tokenizer->next();
            Node *n2 = parseTerm();
            if( n2 == 0 ){
                // Error !
                break;
            }
            if( token_text == "+" )
                n1 = new NodeAdd( n1, n2 );
            else
                n1 = new NodeSub( n1, n2 );
        }
    }
    return n1;
}

Node *Parser::parseTerm()
{
    Node *n1 = parseFactor();
    if( n1 ){
        while( m_token.type() == Token::TYPE_OP_MUL_DIV ){
            string op = m_token.text();
            m_token = m_tokenizer->next();
            Node *n2 = parseFactor();
            if( n2 == 0 ){
                // Error !
                break;
            }
            if( op == "*" )
                n1 = new NodeMul( n1, n2 );
            else
                n1 = new NodeDiv( n1, n2 );
        }
    }
    return n1;
}

Node *Parser::parseFactor()
{
    Node *n = 0;
    if( m_token.type() == Token::TYPE_INTEGER ){
        NodeInteger *nn = new NodeInteger( std::atoi( m_token.text().c_str() ) );
        m_token = m_tokenizer->next();
        return nn;
    }
    else if( m_token.type() == Token::TYPE_NAME ){
        NodeVariable *nv = new NodeVariable( m_token.text() );
        m_token = m_tokenizer->next();
        return nv;
    }
    else if( m_token.type() == Token::TYPE_PAREN_LEFT ){
        m_token = m_tokenizer->next();
        n = parseExpression();
        if( m_token.type() != Token::TYPE_PAREN_RIGHT ){
            // Error !
        }
        m_token = m_tokenizer->next();
    }
    return n;
}


TEST( Tokenizer, canRecognizesNumber )
{
    Tokenizer tokenizer;
    tokenizer.setSource( "12345" );
    Token token = tokenizer.next();
    ASSERT_THAT( token.type(), Eq(Token::TYPE_INTEGER) );
    ASSERT_THAT( token.text(), StrEq("12345") );
}

TEST( Tokenizer, canSkipSpaces )
{
    Tokenizer tokenizer;
    tokenizer.setSource( " \t \n 12345" );
    Token token = tokenizer.next();
    ASSERT_THAT( token.type(), Eq(Token::TYPE_INTEGER) );
    ASSERT_THAT( token.text(), StrEq("12345") );
}

TEST( Tokenizer, canRecognizesName )
{
    Tokenizer tokenizer;
    tokenizer.setSource( "azAZ09" );
    Token token = tokenizer.next();
    ASSERT_THAT( token.type(), Eq(Token::TYPE_NAME) );
    ASSERT_THAT( token.text(), StrEq("azAZ09") );
}

TEST( Tokenizer, canRecognizesKeywordVar )
{
    Tokenizer tokenizer;
    tokenizer.setSource( "var" );
    Token token = tokenizer.next();
    ASSERT_THAT( token.type(), Eq(Token::TYPE_KEY_VAR) );
    ASSERT_THAT( token.text(), StrEq("var") );
}

TEST( Tokenizer, canRecognizesOpAdd )
{
    Tokenizer tokenizer;
    tokenizer.setSource( "+" );
    Token token = tokenizer.next();
    ASSERT_THAT( token.type(), Eq(Token::TYPE_OP_ADD_SUB) );
    ASSERT_THAT( token.text(), StrEq("+") );
}

TEST( Tokenizer, canRecognizesOpSub )
{
    Tokenizer tokenizer;
    tokenizer.setSource( "-" );
    Token token = tokenizer.next();
    ASSERT_THAT( token.type(), Eq(Token::TYPE_OP_ADD_SUB) );
    ASSERT_THAT( token.text(), StrEq("-") );
}

TEST( Tokenizer, canRecognizesOpMul )
{
    Tokenizer tokenizer;
    tokenizer.setSource( "*" );
    Token token = tokenizer.next();
    ASSERT_THAT( token.type(), Eq(Token::TYPE_OP_MUL_DIV) );
    ASSERT_THAT( token.text(), StrEq("*") );
}

TEST( Tokenizer, canRecognizesOpDiv )
{
    Tokenizer tokenizer;
    tokenizer.setSource( "*" );
    Token token = tokenizer.next();
    ASSERT_THAT( token.type(), Eq(Token::TYPE_OP_MUL_DIV) );
    ASSERT_THAT( token.text(), StrEq("*") );
}

TEST( Tokenizer, canRecognizesEqual )
{
    Tokenizer tokenizer;
    tokenizer.setSource( "=" );
    Token token = tokenizer.next();
    ASSERT_THAT( token.type(), Eq(Token::TYPE_EQUAL) );
    ASSERT_THAT( token.text(), StrEq("=") );
}

TEST( Parser, canParseInteger )
{
    Tokenizer tokenizer;
    Parser parser( &tokenizer );
    parser.setSource("12345");
    Node *node = parser.parse();

    NodeInteger *inode = dynamic_cast<NodeInteger *>(node);
    ASSERT_THAT( inode, Ne(static_cast<NodeInteger*>(0)) );
    ASSERT_THAT( inode->value(), Eq(12345) );
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleMock(&argc,argv);
    return RUN_ALL_TESTS();
}
