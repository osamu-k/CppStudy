#include "node.h"
#include "parser.h"

#include <string>
#include <cstdlib>

Parser::Parser( Tokenizer *tokenizer )
    : m_tokenizer(tokenizer)
{
}

Parser::~Parser()
{
}

void Parser::setSource( string source )
{
    m_tokenizer->setSource( source );
    m_token = m_tokenizer->next();
}

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
    m_token = m_tokenizer->next();
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

