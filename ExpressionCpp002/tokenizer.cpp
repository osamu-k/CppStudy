#include "tokenizer.h"
#include "ctype.h"

map<char,Token::Type> Tokenizer::m_typeMap;
map<string, Token::Type> Tokenizer::m_keywordMap;

Tokenizer::Tokenizer()
{
    if( m_typeMap.size() == 0){
        m_typeMap['+'] = Token::TYPE_OPERATOR_ADD;
        m_typeMap['-'] = Token::TYPE_OPERATOR_SUB;
        m_typeMap['*'] = Token::TYPE_OPERATOR_MUL;
        m_typeMap['/'] = Token::TYPE_OPERATOR_DIV;
        m_typeMap['='] = Token::TYPE_ASSIGNMENT;
        m_typeMap['('] = Token::TYPE_PAREN_OPEN;
        m_typeMap[')'] = Token::TYPE_PAREN_CLOSE;
    }
    if( m_keywordMap.size() == 0 ){
        m_keywordMap["var"] = Token::TYPE_KEYWORD_VAR;
    }
}

Tokenizer::~Tokenizer()
{

}

void Tokenizer::setSource( string source )
{
    m_source = source;
    m_nextc = m_source.begin();
}

void Tokenizer::skipSpaces()
{
    while( isspace(*m_nextc) )
        m_nextc++;
}

Token *Tokenizer::next()
{
    skipSpaces();

    Token *token = 0;
    if( (token = makeTokenInteger()) != 0 ){
        return token;
    }
    if( (token = makeTokenName()) != 0 ){
        return token;
    }
    if( (token = makeOperatorToken()) != 0 ){
        return token;
    }
    return new Token(Token::TYPE_END);
}

Token *Tokenizer::makeTokenInteger()
{
    if( isnumber(*m_nextc) ){
        int value = 0;
        while( isnumber(*m_nextc) ){
            value *= 10;
            value += *m_nextc - '0';
            m_nextc++;
        }
        return new TokenInteger(value);
    }
    return 0;
}

Token *Tokenizer::makeTokenName()
{
    if( isalpha(*m_nextc) ){
        string::const_iterator start = m_nextc;
        while( isalnum(*m_nextc) ){
            m_nextc++;
        }
        string name = string( start, m_nextc );
        map<string, Token::Type>::const_iterator it = m_keywordMap.find(name);
        if( it != m_keywordMap.end() ){
            Token *token = new Token(it->second);
            return token;
        }
        return new TokenName( name );
    }
    return 0;
}

Token *Tokenizer::makeOperatorToken()
{
    map<char,Token::Type>::const_iterator it = m_typeMap.find(*m_nextc);
    if( it != m_typeMap.end() ){
        Token *token = new Token(it->second);
        m_nextc++;
        return token;
    }
    return 0;
}
