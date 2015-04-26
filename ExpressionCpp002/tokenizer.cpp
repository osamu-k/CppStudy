#include "tokenizer.h"
#include "ctype.h"

Tokenizer::Tokenizer()
{

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

    int value = 0;
    while( isnumber(*m_nextc) ){
        value *= 10;
        value += *m_nextc - '0';
        m_nextc++;
    }
    return new TokenInteger(value);
}
