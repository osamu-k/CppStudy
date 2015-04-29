#ifndef NODE_H
#define NODE_H

#include "nodevisitor.h"
#include <string>

using namespace std;

class Node
{
public:
    enum Type {
        TYPE_UNDEFINED,
        TYPE_INTEGER,
        TYPE_ADD,
        TYPE_SUB,
        TYPE_MUL,
        TYPE_DIV,
        TYPE_VAR_DECL,
        TYPE_VAR_REF,
        TYPE_ASSIGN,
        TYPE_PLUS,
        TYPE_MINUS
    };

    Node( Type type = TYPE_UNDEFINED )
        : m_type(type)
    { }

    virtual ~Node()
    { }

    Type type()
    { return m_type; }

    virtual void acceptVisitor( NodeVisitor *visitor ) = 0;

private:
    Type m_type;
};

class NodeInteger : public  Node
{
public:
    NodeInteger( int value )
        : Node(Node::TYPE_INTEGER),m_value(value)
    { }

    ~NodeInteger()
    { }

    int value()
    { return m_value; }

    void acceptVisitor( NodeVisitor *visitor )
    {
        visitor->visit( this );
    }

private:
    int m_value;
};

class NodeInfix : public Node
{
public:
    NodeInfix( Type type, Node *operand1, Node *operand2 )
        :Node(type), m_operand1(operand1), m_operand2(operand2)
    { }

    ~NodeInfix()
    {
        if( m_operand1 ) delete m_operand1;
        if( m_operand2 ) delete m_operand2;
    }

    Node *operand1()
    { return m_operand1; }

    Node *operand2()
    { return m_operand2; }

private:
     Node *m_operand1;
     Node *m_operand2;
};

class NodeAdd : public NodeInfix
{
public:
    NodeAdd( Node *operand1, Node *operand2 )
        : NodeInfix(Node::TYPE_ADD, operand1, operand2)
    {}

    ~NodeAdd()
    {}

    void acceptVisitor( NodeVisitor *visitor )
    {
        operand1()->acceptVisitor(visitor);
        operand2()->acceptVisitor(visitor);
        visitor->visit( this );
    }
};

class NodeSub : public NodeInfix
{
public:
    NodeSub( Node *operand1, Node *operand2 )
        : NodeInfix(Node::TYPE_SUB, operand1, operand2)
    {}

    ~NodeSub()
    {}

    void acceptVisitor( NodeVisitor *visitor )
    {
        operand1()->acceptVisitor(visitor);
        operand2()->acceptVisitor(visitor);
        visitor->visit( this );
    }
};

class NodeMul : public NodeInfix
{
public:
    NodeMul( Node *operand1, Node *operand2 )
        : NodeInfix(Node::TYPE_MUL, operand1, operand2)
    {}

    ~NodeMul()
    {}

    void acceptVisitor( NodeVisitor *visitor )
    {
        operand1()->acceptVisitor(visitor);
        operand2()->acceptVisitor(visitor);
        visitor->visit( this );
    }
};

class NodeDiv : public NodeInfix
{
public:
    NodeDiv( Node *operand1, Node *operand2 )
        : NodeInfix(Node::TYPE_DIV, operand1, operand2)
    {}

    ~NodeDiv()
    {}

    void acceptVisitor( NodeVisitor *visitor )
    {
        operand1()->acceptVisitor(visitor);
        operand2()->acceptVisitor(visitor);
        visitor->visit( this );
    }
};

class NodeVarDecl : public Node
{
public:
    NodeVarDecl( string name )
        :Node(Node::TYPE_VAR_DECL), m_name(name)
    {}

    ~NodeVarDecl()
    {}

    string name()
    { return m_name; }

    void acceptVisitor( NodeVisitor *visitor )
    {
        visitor->visit( this );
    }

private:
    string m_name;
};

class NodeVarRef : public Node
{
public:
    NodeVarRef( string name )
        :Node(Node::TYPE_VAR_REF), m_name(name)
    {}

    ~NodeVarRef()
    {}

    string name()
    { return m_name; }

    void acceptVisitor( NodeVisitor *visitor )
    {
        visitor->visit( this );
    }

private:
    string m_name;
};

class NodeAssign : public Node
{
public:
    NodeAssign( NodeVarDecl *var, Node *value )
        : Node(Node::TYPE_ASSIGN), m_var(var), m_value(value)
    {}

    ~NodeAssign()
    {
        if( m_var ) delete m_var;
        if( m_value ) delete m_value;
    }

    NodeVarDecl *var()
    { return m_var; }

    Node *value()
    { return m_value; }

    void acceptVisitor( NodeVisitor *visitor )
    {
        var()->acceptVisitor(visitor);
        value()->acceptVisitor(visitor);
        visitor->visit( this );
    }

private:
    NodeVarDecl *m_var;
    Node *m_value;
};

class NodePrefix : public Node
{
public:
    NodePrefix( Node::Type type, Node *operand )
        : Node(type), m_operand(operand)
    {}

    ~NodePrefix()
    {
        if( m_operand ) delete m_operand;
    }

    Node *operand()
    { return m_operand; }

private:
    Node *m_operand;
};

class NodePlus : public NodePrefix
{
public:
    NodePlus( Node *operand )
        : NodePrefix(Node::TYPE_PLUS, operand)
    {}

    ~NodePlus()
    {}

    void acceptVisitor( NodeVisitor *visitor )
    {
        operand()->acceptVisitor( visitor );
        visitor->visit( this );
    }
};

class NodeMinus : public NodePrefix
{
public:
    NodeMinus( Node *operand )
        : NodePrefix(Node::TYPE_MINUS, operand)
    {}

    ~NodeMinus()
    {}

    void acceptVisitor( NodeVisitor *visitor )
    {
        operand()->acceptVisitor( visitor );
        visitor->visit( this );
    }
};

#endif // NODE_H
