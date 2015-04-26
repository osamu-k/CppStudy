#include "token.h"

Token::Token( Type type, string text )
    : m_type(type),m_text(text)
{
}

Token::Token( Type type, char c )
    : m_type(type),m_text(string(1,c))
{
}

Token::~Token()
{
}

Token::Type Token::type()
{
    return m_type;
}

string Token::text()
{
    return m_text;
}
