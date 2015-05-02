#ifndef PARSER_H
#define PARSER_H

#include "node.h"
#include "tokenizer.h"

class Parser
{
public:
    Parser( Tokenizer *tokenizer )
        : m_tokenizer(tokenizer),m_token(0),m_error(false)
    {}

    ~Parser()
    {}

    Node *parse( string source );

    void setError( string message )
    {
        m_error = true;
        m_errorMessage = message;
    }

    bool isError()
    {
        return m_error;
    }
    string errorMessage()
    {
        return m_errorMessage;
    }

private:
    Node *parseExpression();
    Node *parseTerm();
    Node *parsePrefix();
    Node *parseFactor();
    Node *parseAssign();
    void nextToken();
    Tokenizer *m_tokenizer;
    Token *m_token;
    bool m_error;
    string m_errorMessage;
};

#endif // PARSER_H
