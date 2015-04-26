#include "nodevisitor.h"

void NodeVisitor::visitInteger(  NodeInteger *ni )
{
    push( ni->value() );
}

void NodeVisitor::visitVariable( NodeVariable *nv )
{
    push( m_var_map[ nv->name() ] );
}

void NodeVisitor::visitAdd( NodeAdd *na )
{
    int right = pop();
    int left = pop();
    push( left + right );
}

void NodeVisitor::visitSub( NodeSub *ns )
{
    int right = pop();
    int left = pop();
    push( left - right );
}

void NodeVisitor::visitMul( NodeMul *nm )
{
    int right = pop();
    int left = pop();
    push( left * right );
}

void NodeVisitor::visitDiv( NodeDiv *nd )
{
    int right = pop();
    int left = pop();
    push( left / right );
}

void NodeVisitor::visitAssign( NodeAssign *na )
{
    int  value = pop();
    m_var_map[ na->variable()->name() ] = value;
    push( value );
}

int NodeVisitor::value()
{
    return pop();
}
