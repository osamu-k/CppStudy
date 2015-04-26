#ifndef NODE_H
#define NODE_H

#include "visitor.h"

#include <map>
#include <string>
using namespace std;

class Node
{
public:
    enum Type{
        TYPE_UNDEFINED,
        TYPE_INTEGER,
        TYPE_VARIABLE,
        TYPE_ADD,
        TYPE_SUB,
        TYPE_MUL,
        TYPE_DIV,
        TYPE_ASSIGN
    };
    Node( Type type = TYPE_UNDEFINED );
    virtual ~Node();
    Type type();
    virtual int evaluate( map<string,int> &context ) = 0;

    virtual void visit( Visitor *visitor ) = 0;

private:
    Type m_type;
};


class NodeInteger : public Node
{
public:
    NodeInteger( long value = 0 )
        :Node( Node::TYPE_INTEGER ), m_value(value)
    {
    }

    virtual ~NodeInteger()
    {
    }

    long value()
    {
        return m_value;
    }

    int evaluate( map<string,int> &context )
    {
        return m_value;
    }

    void visit( Visitor *visitor )
    {
        visitor->visitInteger( this );
    }

private:
    long m_value;
};

class NodeVariable : public Node
{
public:
    NodeVariable( string name = string() )
        :Node( Node::TYPE_VARIABLE ), m_name(name)
    {
    }

    virtual ~NodeVariable()
    {
    }

    string name()
    {
        return m_name;
    }
    int evaluate( map<string,int> &context )
    {
        return context[m_name];
    }

    void visit( Visitor *visitor )
    {
        return visitor->visitVariable( this );
    }

private:
    string m_name;
};

class NodeBinary : public Node
{
public:
    NodeBinary( Node::Type type,  Node *left, Node *right )
        : Node(type), m_left( left ), m_right( right )
    {
    }

    ~NodeBinary()
    {
    }

    Node *left()
    {
        return m_left;
    }

    Node *right()
    {
        return m_right;
    }

protected:
    Node *m_left;
    Node *m_right;
};

class NodeAdd : public NodeBinary
{
public:
    NodeAdd( Node *left, Node *right )
        :NodeBinary( Node::TYPE_ADD, left, right )
    {
    }

    ~NodeAdd()
    {
    }

    int evaluate( map<string,int> &context )
    {
        return m_left->evaluate(context) + m_right->evaluate(context);
    }

    void visit( Visitor *visitor )
    {
        m_left->visit( visitor );
        m_right->visit( visitor );
        visitor->visitAdd( this );
    }
};

class NodeSub : public NodeBinary
{
public:
    NodeSub( Node *left, Node *right )
        :NodeBinary( Node::TYPE_SUB, left, right )
    {
    }

    ~NodeSub()
    {
    }

    int evaluate( map<string,int> &context )
    {
        return m_left->evaluate(context) - m_right->evaluate(context);
    }

    void visit( Visitor *visitor )
    {
        m_left->visit( visitor );
        m_right->visit( visitor );
        visitor->visitSub( this );
    }
};

class NodeMul : public NodeBinary
{
public:
    NodeMul( Node *left, Node *right )
        :NodeBinary( Node::TYPE_MUL, left, right )
    {
    }

    ~NodeMul()
    {
    }

    int evaluate( map<string,int> &context )
    {
        return m_left->evaluate(context) * m_right->evaluate(context);
    }

    void visit( Visitor *visitor )
    {
        m_left->visit( visitor );
        m_right->visit( visitor );
        visitor->visitMul( this );
    }
};

class NodeDiv : public NodeBinary
{
public:
    NodeDiv( Node *left, Node *right )
        :NodeBinary( Node::TYPE_DIV, left, right )
    {
    }

    ~NodeDiv()
    {
    }

    int evaluate( map<string,int> &context )
    {
        return m_left->evaluate(context) / m_right->evaluate(context);
    }

    void visit( Visitor *visitor )
    {
        m_left->visit( visitor );
        m_right->visit( visitor );
        visitor->visitDiv( this );
    }
};

class NodeAssign : public Node
{
public:
    NodeAssign( NodeVariable *var, Node *value )
        : m_variable( var ), m_value( value )
    {
    }

    ~NodeAssign()
    {
    }

    NodeVariable *variable()
    {
        return m_variable;
    }

    Node *value()
    {
        return m_value;
    }

    int evaluate( map<string,int> &context )
    {
        int value = m_value->evaluate(context);
        context[m_variable->name()] = value;
        return value;
    }

    void visit( Visitor *visitor )
    {
        m_value->visit( visitor );
        visitor->visitAssign( this );
    }

private:
    NodeVariable *m_variable;
    Node *m_value;
};

#endif // NODE_H
