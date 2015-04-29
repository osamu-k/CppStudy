#ifndef NODEVISITOR_H
#define NODEVISITOR_H

class NodeInteger;
class NodeVarDecl;
class NodeAdd;
class NodeSub;
class NodeMul;
class NodeDiv;
class NodePlus;
class NodeMinus;
class NodeVarRef;
class NodeAssign;

class NodeVisitor
{
public:
    NodeVisitor()
    {}

    virtual ~NodeVisitor()
    {}

    virtual void visit( NodeInteger * ) = 0;
    virtual void visit( NodeVarDecl * ) = 0;
    virtual void visit( NodeAdd * ) = 0;
    virtual void visit( NodeSub * ) = 0;
    virtual void visit( NodeMul * ) = 0;
    virtual void visit( NodeDiv * ) = 0;
    virtual void visit( NodePlus * ) = 0;
    virtual void visit( NodeMinus * ) = 0;
    virtual void visit( NodeVarRef * ) = 0;
    virtual void visit( NodeAssign * ) = 0;
};

#endif // NODEVISITOR_H
