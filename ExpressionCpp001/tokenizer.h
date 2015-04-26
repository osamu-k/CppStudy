#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "token.h"

class Tokenizer
{
public:
    Tokenizer();
    ~Tokenizer();
    void setSource( const string &source );
    Token next();

private:
    void skipSpace();
    Token makeInteger();
    Token makeName();
    Token makeOperator();
    string m_source;
    string::iterator m_sourceIt;
};

#endif // TOKENIZER_H
