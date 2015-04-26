#include "tokenizer.h"

Tokenizer::Tokenizer()
{
}

Tokenizer::~Tokenizer()
{
}

void Tokenizer::setSource( const string &source )
{
    m_source = source;
    m_sourceIt = m_source.begin();
}

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
