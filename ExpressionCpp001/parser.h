#ifndef PARSER_H
#define PARSER_H

#include "tokenizer.h"

class Node;

class Parser{
public:
    Parser( Tokenizer *tokenizer );
    ~Parser();
    void setSource( string source );
    Node *parse();
    Node *parseAssignment();
    Node *parseExpression();
    Node *parseTerm();
    Node *parseFactor();

private:
    Tokenizer *m_tokenizer;
    Token m_token;
};

#endif // PARSER_H
