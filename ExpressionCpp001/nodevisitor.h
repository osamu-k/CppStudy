#ifndef NODEVISITOR_H
#define NODEVISITOR_H

#include "node.h"
#include "visitor.h"
#include <list>
#include <map>

class NodeVisitor : public Visitor
{
public:
    NodeVisitor()
    {}
    void visitInteger( NodeInteger *ni );
    void visitVariable( NodeVariable *nv );
    void visitAdd( NodeAdd *na );
    void visitSub( NodeSub *ns );
    void visitMul(NodeMul *nm );
    void visitDiv( NodeDiv *nv );
    void visitAssign( NodeAssign *na );

    int value();

protected:
    void push( int value )
    {
        m_stack.push_front( value );
    }

    int pop()
    {
        int value = m_stack.front();
        m_stack.pop_front();
        return value;
    }

private:
    std::map<string,int> m_var_map;
    std::list<int> m_stack;
};

#endif // NODEVISITOR_H
