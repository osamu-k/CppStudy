#include "parser.h"

Node *Parser::parse( string source )
{
    m_tokenizer->setSource( source );
    nextToken();
    if( m_token == 0 ) return 0;

    if( m_token->type() == Token::TYPE_KEYWORD_VAR )
        return parseAssign();
    else
        return parseExpression();
}

Node *Parser::parseExpression()
{
    Node *operand1 = parseTerm();
    if( operand1 == 0 ){
        // Error !
        return 0;
    }
    while( true ){
        if( m_token->type() == Token::TYPE_OPERATOR_ADD ){
            nextToken();
            Node *operand2 = parseTerm();
            if( operand2 == 0 ){
                // Error !
                delete operand1;
                return 0;
            }
            operand1 = new NodeAdd( operand1, operand2 );
        }
        if( m_token->type() == Token::TYPE_OPERATOR_SUB ){
            nextToken();
            Node *operand2 = parseTerm();
            if( operand2 == 0 ){
                // Error !
                delete operand1;
                return 0;
            }
            operand1 = new NodeSub( operand1, operand2 );
        }
        else{
            break;
        }
    }
    return operand1;
}

Node *Parser::parseTerm()
{
    Node *operand1 = parsePrefix();
    if( operand1 == 0 ){
        // Error !
        return 0;
    }
    while(true){
        if( m_token->type() == Token::TYPE_OPERATOR_MUL ){
            nextToken();
            Node *operand2 = parsePrefix();
            if( operand2 == 0 ){
                // Error !
                delete operand1;
                return 0;
            }
            operand1 = new NodeMul( operand1, operand2 );
        }
        if( m_token->type() == Token::TYPE_OPERATOR_DIV ){
            nextToken();
            Node *operand2 = parsePrefix();
            if( operand2 == 0 ){
                // Error !
                delete operand1;
                return 0;
            }
            operand1 = new NodeDiv( operand1, operand2 );
        }
        else{
            break;
        }
    }
    return operand1;
}

Node *Parser::parsePrefix()
{
    if( m_token->type() == Token::TYPE_OPERATOR_ADD ){
        nextToken();
        Node *operand = parseFactor();
        if( operand == 0 ){
            // Error
            delete operand;
            return 0;
        }
        return new NodePlus( operand );
    }
    if( m_token->type() == Token::TYPE_OPERATOR_SUB ){
        nextToken();
        Node *operand = parseFactor();
        if( operand == 0 ){
            // Error
            delete operand;
            return 0;
        }
        return new NodeMinus( operand );
    }
    return parseFactor();
}

Node *Parser::parseFactor()
{
    if( m_token->type() == Token::TYPE_INTEGER ){
        TokenInteger *tokenInt = dynamic_cast<TokenInteger *>(m_token);
        Node *node = new NodeInteger( tokenInt->value() );
        nextToken();
        return node;
    }
    if( m_token->type() == Token::TYPE_NAME ){
        TokenName *tokenName = dynamic_cast<TokenName *>(m_token);
        Node *node = new NodeVarRef(tokenName->name());
        nextToken();
        return node;
    }
    if( m_token->type() == Token::TYPE_PAREN_OPEN ){
        nextToken();
        Node *node = parseExpression();
        if( m_token->type() != Token::TYPE_PAREN_CLOSE ){
            // Error
            delete node;
            return 0;
        }
        nextToken();
        return node;
    }
    return 0;
}

Node *Parser::parseAssign()
{
    nextToken();
    if( m_token->type() != Token::TYPE_NAME ){
        // Error !
        return 0;
    }
    TokenName *tokenName = dynamic_cast<TokenName*>(m_token);
    NodeVarDecl *varDecl = new NodeVarDecl( tokenName->name() );

    nextToken();
    if( m_token->type() != Token::TYPE_ASSIGNMENT ){
        // Error !
        delete varDecl;
        return 0;
    }

    nextToken();
    Node *value = parseExpression();
    if( value == 0 ){
        // Error !
        delete varDecl;
        return 0;
    }
    return new NodeAssign( varDecl, value );
}

void Parser::nextToken()
{
    if( m_token ) delete m_token;
    m_token = m_tokenizer->next();
}
