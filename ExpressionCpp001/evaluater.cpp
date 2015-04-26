#include "evaluater.h"
#include "node.h"
#include "parser.h"

int Evaluater::evaluate( string expression )
{
    m_parser->setSource( expression );
    return evaluateNode( m_parser->parse() );
}

int Evaluater::evaluateNode( Node *node )
{
    if( node )
        return node->evaluate( m_context );
    else
        return 0;
}

