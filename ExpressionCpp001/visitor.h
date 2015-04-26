#ifndef VISITOR_H
#define VISITOR_H

class NodeInteger;
class NodeVariable;
class NodeAdd;
class NodeSub;
class NodeMul;
class NodeDiv;
class NodeAssign;

class Visitor
{
public:
    virtual void visitInteger( NodeInteger *ni ) = 0;
    virtual void visitVariable( NodeVariable *nv ) = 0;
    virtual void visitAdd( NodeAdd *na ) = 0;
    virtual void visitSub( NodeSub *ns ) = 0;
    virtual void visitMul(NodeMul *nm ) = 0;
    virtual void visitDiv( NodeDiv *nv ) = 0;
    virtual void visitAssign( NodeAssign *na ) = 0;

protected:
    Visitor()
    {}

    virtual ~Visitor()
    {}
};

#endif // VISITOR_H
