#include "testnode.h"

TEST_F( TestNode, canCreateNodeInteger )
{
    NodeInteger *node = new NodeInteger( 12345 );
    ASSERT_THAT( node->type(), Eq(Node::TYPE_INTEGER) );
    ASSERT_THAT( node->value(), Eq(12345) );
    delete node;
}

void assertInfixNode( NodeInfix *node, Node::Type type, Node *operand1, Node *operand2 )
{
    ASSERT_THAT( node->type(), Eq(type) );
    ASSERT_THAT( node->operand1(), Eq(operand1) );
    ASSERT_THAT( node->operand2(), Eq(operand2) );
}

TEST_F( TestNode, canCreateNodeAdd )
{
    Node *nodeInt1 = new NodeInteger(1);
    Node *nodeInt2 = new NodeInteger(2);
    NodeAdd *node = new NodeAdd( nodeInt1, nodeInt2 );
    assertInfixNode( node, Node::TYPE_ADD, nodeInt1, nodeInt2 );
    delete node;
}

TEST_F( TestNode, canCreateNodeSub )
{
    Node *nodeInt1 = new NodeInteger(1);
    Node *nodeInt2 = new NodeInteger(2);
    NodeSub *node = new NodeSub( nodeInt1, nodeInt2 );
    assertInfixNode( node, Node::TYPE_SUB, nodeInt1, nodeInt2 );
    delete node;
}

TEST_F( TestNode, canCreateNodeMul )
{
    Node *nodeInt1 = new NodeInteger(1);
    Node *nodeInt2 = new NodeInteger(2);
    NodeMul *node = new NodeMul( nodeInt1, nodeInt2 );
    assertInfixNode( node, Node::TYPE_MUL, nodeInt1, nodeInt2 );
    delete node;
}

TEST_F( TestNode, canCreateNodeDiv )
{
    Node *nodeInt1 = new NodeInteger(1);
    Node *nodeInt2 = new NodeInteger(2);
    NodeDiv *node = new NodeDiv( nodeInt1, nodeInt2 );
    assertInfixNode( node, Node::TYPE_DIV, nodeInt1, nodeInt2 );
    delete node;
}

TEST_F( TestNode, canCreateNodeVarDecl )
{
    NodeVarDecl *node = new NodeVarDecl( "xyz" );
    ASSERT_THAT( node->type(), Eq(Node::TYPE_VAR_DECL) );
    ASSERT_THAT( node->name(), StrEq("xyz") );
    delete node;
}

TEST_F( TestNode, canCreateNodeVarRef )
{
    NodeVarRef *node = new NodeVarRef( "xyz" );
    ASSERT_THAT( node->type(), Eq(Node::TYPE_VAR_REF) );
    ASSERT_THAT( node->name(), StrEq("xyz") );
    delete node;
}

TEST_F( TestNode, canCreateNodeAssign )
{
    NodeVarDecl *varDecl = new NodeVarDecl( "x" );
    Node *value = new NodeInteger(1);
    NodeAssign *node = new NodeAssign( varDecl, value );
    ASSERT_THAT( node->type(), Eq(Node::TYPE_ASSIGN) );
    ASSERT_THAT( node->var(), Eq(varDecl) );
    ASSERT_THAT( node->value(), Eq(value) );
    delete node;
}

TEST_F( TestNode, canCreateNodePrefixPlus )
{
    Node *nodeInt1 = new NodeInteger(1);
    NodePlus *node = new NodePlus( nodeInt1 );
    ASSERT_THAT( node->type(), Eq(Node::TYPE_PLUS) );
    ASSERT_THAT( node->operand(), Eq(nodeInt1) );
    delete node;
}

TEST_F( TestNode, canCreateNodePrefixMinus )
{
    Node *nodeInt1 = new NodeInteger(1);
    NodeMinus *node = new NodeMinus( nodeInt1 );
    ASSERT_THAT( node->type(), Eq(Node::TYPE_MINUS) );
    ASSERT_THAT( node->operand(), Eq(nodeInt1) );
    delete node;
}
