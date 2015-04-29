#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "token.h"
#include <map>
#include <string>

using namespace std;

class Tokenizer
{
public:
    Tokenizer();
    ~Tokenizer();
    void setSource( string source );
    Token *next();

private:
    void skipSpaces();
    Token *makeTokenInteger();
    Token *makeTokenName();
    Token *makeOperatorToken();
    string m_source;
    string::const_iterator m_nextc;
    static map<char,Token::Type> m_typeMap;
    static map<string, Token::Type> m_keywordMap;
};

#endif // TOKENIZER_H
