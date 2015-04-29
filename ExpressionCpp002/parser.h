#ifndef PARSER_H
#define PARSER_H

#include "node.h"
#include "tokenizer.h"

class Parser
{
public:
    Parser( Tokenizer *tokenizer )
        : m_tokenizer(tokenizer),m_token(0)
    {}

    ~Parser()
    {}

    Node *parse( string source );

private:
    Node *parseExpression();
    Node *parseTerm();
    Node *parsePrefix();
    Node *parseFactor();
    Node *parseAssign();
    void nextToken();
    Tokenizer *m_tokenizer;
    Token *m_token;
};

#endif // PARSER_H
