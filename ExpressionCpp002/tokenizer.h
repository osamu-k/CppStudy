#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "token.h"
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
    string m_source;
    string::const_iterator m_nextc;
};

#endif // TOKENIZER_H
