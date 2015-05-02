#include "testparser.h"

#include "parser.h"
#include "tokenizer.h"
#include "token.h"

using namespace testing;

void assertInteger( Node *node, int value )
{
    ASSERT_THAT( node, Ne(static_cast<Node*>(0)) );
    ASSERT_THAT( node->type(), Eq(Node::TYPE_INTEGER) );
    NodeInteger *nodei = dynamic_cast<NodeInteger*>(node);
    ASSERT_THAT( nodei->value(), Eq(value) );
}

TEST_F( TestParser, recognizesInteger )
{
    Node *node = parser.parse( "123" );
    assertInteger( node, 123 );
    delete node;
    node = 0;

    node = parser.parse( "45678" );
    assertInteger( node, 45678 );
    delete node;
}

TEST_F( TestParser, recognizesVarRef )
{
    Node *node = parser.parse("xyz");
    ASSERT_THAT( node->type(), Eq(Node::TYPE_VAR_REF) );
    NodeVarRef *nodeVarRef = dynamic_cast<NodeVarRef *>(node);
    ASSERT_THAT( nodeVarRef->name(), StrEq("xyz") );
    delete node;
}

TEST_F( TestParser, recognizesPrefixPlus )
{
    Node *node = parser.parse( "+123");
    ASSERT_THAT( node->type(), Eq(Node::TYPE_PLUS) );
    NodePlus *nodePlus = dynamic_cast<NodePlus*>(node);
    ASSERT_THAT( nodePlus->operand()->type(), Eq(Node::TYPE_INTEGER) );
    NodeInteger *nodeInt = dynamic_cast<NodeInteger *>(nodePlus->operand());
    ASSERT_THAT( nodeInt->value(), Eq(123) );
    delete node;
}

TEST_F( TestParser, recognizesPrefixMinus )
{
    Node *node = parser.parse("-123");
    ASSERT_THAT( node->type(), Eq(Node::TYPE_MINUS) );
    NodeMinus *nodeMinus = dynamic_cast<NodeMinus*>(node);
    ASSERT_THAT( nodeMinus->operand()->type(), Eq(Node::TYPE_INTEGER) );
    NodeInteger *nodeInt = dynamic_cast<NodeInteger *>(nodeMinus->operand());
    ASSERT_THAT( nodeInt->value(), Eq(123) );
    delete node;
}

TEST_F( TestParser, recognizesTermMul )
{
    Node *node = parser.parse("123*xyz");
    ASSERT_THAT( node->type(), Eq(Node::TYPE_MUL) );
    NodeMul *nodeMul = dynamic_cast<NodeMul *>(node);
    Node *operand1 = nodeMul->operand1();
    Node *operand2 = nodeMul->operand2();
    ASSERT_THAT( operand1->type(), Eq(Node::TYPE_INTEGER) );
    ASSERT_THAT( operand2->type(), Eq(Node::TYPE_VAR_REF) );
    delete node;
}

TEST_F( TestParser, recognizesTermDiv )
{
    Node *node = parser.parse("+123/-xyz");
    ASSERT_THAT( node->type(), Eq(Node::TYPE_DIV) );
    NodeDiv *nodeDiv = dynamic_cast<NodeDiv *>(node);
    Node *operand1 = nodeDiv->operand1();
    Node *operand2 = nodeDiv->operand2();
    ASSERT_THAT( operand1->type(), Eq(Node::TYPE_PLUS) );
    ASSERT_THAT( operand2->type(), Eq(Node::TYPE_MINUS) );
    delete node;
}

TEST_F( TestParser, recognizesTermRepetition)
{
    Node *node = parser.parse("123*xyz/-123");
    ASSERT_THAT( node->type(), Eq(Node::TYPE_DIV) );
    NodeDiv *nodeDiv = dynamic_cast<NodeDiv *>(node);
    Node *operand1 = nodeDiv->operand1();
    Node *operand2 = nodeDiv->operand2();
    ASSERT_THAT( operand1->type(), Eq(Node::TYPE_MUL) );

    NodeMul *nodeMul = dynamic_cast<NodeMul*>(operand1);
    Node *mulop1 = nodeMul->operand1();
    Node *mulop2 = nodeMul->operand2();
    ASSERT_THAT( mulop1->type(), Eq(Node::TYPE_INTEGER) );
    ASSERT_THAT( mulop2->type(), Eq(Node::TYPE_VAR_REF) );

    ASSERT_THAT( operand2->type(), Eq(Node::TYPE_MINUS) );

    NodeMinus *nodeMin = dynamic_cast<NodeMinus*>(operand2);
    Node *minop = nodeMin->operand();
    ASSERT_THAT( minop->type(), Eq(Node::TYPE_INTEGER) );

    delete node;
}

TEST_F( TestParser, recognizesTermRepetition2)
{
    Node *node = parser.parse("123*456*789");
    ASSERT_THAT( node->type(), Eq(Node::TYPE_MUL) );
    NodeMul *nodeMul1 = dynamic_cast<NodeMul *>(node);
    Node *operand1 = nodeMul1->operand1();
    Node *operand2 = nodeMul1->operand2();
    ASSERT_THAT( operand1->type(), Eq(Node::TYPE_MUL) );

    NodeMul *nodeMul2 = dynamic_cast<NodeMul*>(operand1);
    Node *mulop1 = nodeMul2->operand1();
    Node *mulop2 = nodeMul2->operand2();
    ASSERT_THAT( mulop1->type(), Eq(Node::TYPE_INTEGER) );
    ASSERT_THAT( mulop2->type(), Eq(Node::TYPE_INTEGER) );

    ASSERT_THAT( operand2->type(), Eq(Node::TYPE_INTEGER) );

    delete node;
}

TEST_F( TestParser, recognizesAdd )
{
    Node *node = parser.parse("123+xyz");
    ASSERT_THAT( node->type(), Eq(Node::TYPE_ADD) );
    NodeAdd *nodeAdd = dynamic_cast<NodeAdd *>(node);
    Node *operand1 = nodeAdd->operand1();
    Node *operand2 = nodeAdd->operand2();
    ASSERT_THAT( operand1->type(), Eq(Node::TYPE_INTEGER) );
    ASSERT_THAT( operand2->type(), Eq(Node::TYPE_VAR_REF) );
    delete node;
}

TEST_F( TestParser, recognizesTermSub )
{
    Node *node = parser.parse("+123--xyz");
    ASSERT_THAT( node->type(), Eq(Node::TYPE_SUB) );
    NodeSub *nodeSub = dynamic_cast<NodeSub *>(node);
    Node *operand1 = nodeSub->operand1();
    Node *operand2 = nodeSub->operand2();
    ASSERT_THAT( operand1->type(), Eq(Node::TYPE_PLUS) );
    ASSERT_THAT( operand2->type(), Eq(Node::TYPE_MINUS) );
    delete node;
}

TEST_F( TestParser, recognizesExpressionRepetition)
{
    Node *node = parser.parse("123+xyz--123");
    ASSERT_THAT( node->type(), Eq(Node::TYPE_SUB) );
    NodeSub *nodeSub = dynamic_cast<NodeSub *>(node);
    Node *operand1 = nodeSub->operand1();
    Node *operand2 = nodeSub->operand2();

    ASSERT_THAT( operand1->type(), Eq(Node::TYPE_ADD) );
    NodeAdd *nodeAdd = dynamic_cast<NodeAdd*>(operand1);
    Node *addop1 = nodeAdd->operand1();
    Node *addop2 = nodeAdd->operand2();
    ASSERT_THAT( addop1->type(), Eq(Node::TYPE_INTEGER) );
    ASSERT_THAT( addop2->type(), Eq(Node::TYPE_VAR_REF) );

    ASSERT_THAT( operand2->type(), Eq(Node::TYPE_MINUS) );
    NodeMinus *nodeMin = dynamic_cast<NodeMinus*>(operand2);
    Node *minop = nodeMin->operand();
    ASSERT_THAT( minop->type(), Eq(Node::TYPE_INTEGER) );

    delete node;
}

TEST_F( TestParser, recognizesExpressionRepetition2 )
{
    Node *node = parser.parse("123+456+789");
    ASSERT_THAT( node->type(), Eq(Node::TYPE_ADD) );
    NodeAdd *nodeAdd1 = dynamic_cast<NodeAdd *>(node);
    Node *operand1 = nodeAdd1->operand1();
    Node *operand2 = nodeAdd1->operand2();

    ASSERT_THAT( operand1->type(), Eq(Node::TYPE_ADD) );
    NodeAdd *nodeAdd2 = dynamic_cast<NodeAdd*>(operand1);
    Node *addop1 = nodeAdd2->operand1();
    Node *addop2 = nodeAdd2->operand2();
    ASSERT_THAT( addop1->type(), Eq(Node::TYPE_INTEGER) );
    ASSERT_THAT( addop2->type(), Eq(Node::TYPE_INTEGER) );

    ASSERT_THAT( operand2->type(), Eq(Node::TYPE_INTEGER) );

    delete node;
}

TEST_F( TestParser, recognizesTermInExpression ){
    Node *node = parser.parse("123*x+456/y-+789*-z");
    ASSERT_THAT( node->type(), Eq(Node::TYPE_SUB) );
    NodeSub *nodeSub = dynamic_cast<NodeSub*>(node);
    Node *operand1 = nodeSub->operand1();
    Node *operand2 = nodeSub->operand2();

    ASSERT_THAT( operand1->type(), Eq(Node::TYPE_ADD) );
    NodeAdd *nodeAdd = dynamic_cast<NodeAdd*>(operand1);
    Node *addop1 = nodeAdd->operand1();
    Node *addop2 = nodeAdd->operand2();
    ASSERT_THAT( addop1->type(), Eq(Node::TYPE_MUL) );
    ASSERT_THAT( addop2->type(), Eq(Node::TYPE_DIV) );

    ASSERT_THAT( operand2->type(), Eq(Node::TYPE_MUL) );

    delete node;
}

TEST_F( TestParser, recognizesIntegerInParenthesis )
{
    Node *node = parser.parse("(123)");
    ASSERT_THAT( node->type(), Eq(Node::TYPE_INTEGER) );
    NodeInteger *nodeInt = dynamic_cast<NodeInteger*>(node);
    ASSERT_THAT( nodeInt->value(), Eq(123) );
}

TEST_F( TestParser, recognizesVarRefInParenthesis )
{
    Node *node = parser.parse("(xyz)");
    ASSERT_THAT( node->type(), Eq(Node::TYPE_VAR_REF) );
    NodeVarRef *nodeVarRef = dynamic_cast<NodeVarRef*>(node);
    ASSERT_THAT( nodeVarRef->name(), StrEq("xyz") );
}

TEST_F( TestParser, recognizesPrefixInParenthesis )
{
    Node *node = parser.parse("(-123)");
    ASSERT_THAT( node->type(), Eq(Node::TYPE_MINUS) );
    NodeMinus *nodeMinus = dynamic_cast<NodeMinus*>(node);
    Node *operand = nodeMinus->operand();
    ASSERT_THAT( operand->type(), Eq(Node::TYPE_INTEGER) );
    NodeInteger *nodeInt = dynamic_cast<NodeInteger*>(operand);
    ASSERT_THAT( nodeInt->value(), Eq(123) );
}

TEST_F( TestParser, recognizesTermInParenthesis )
{
    Node *node = parser.parse("(123*xyz)");
    ASSERT_THAT( node->type(), Eq(Node::TYPE_MUL) );
    NodeMul *nodeMul = dynamic_cast<NodeMul*>(node);
    Node *operand1 = nodeMul->operand1();
    Node *operand2 = nodeMul->operand2();
    ASSERT_THAT( operand1->type(), Eq(Node::TYPE_INTEGER) );
    ASSERT_THAT( operand2->type(), Eq(Node::TYPE_VAR_REF) );
}

TEST_F( TestParser, recognizesExpressionInParenthesis )
{
    Node *node = parser.parse("(123+xyz)");
    ASSERT_THAT( node->type(), Eq(Node::TYPE_ADD) );
    NodeAdd *nodeAdd = dynamic_cast<NodeAdd*>(node);
    Node *operand1 = nodeAdd->operand1();
    Node *operand2 = nodeAdd->operand2();
    ASSERT_THAT( operand1->type(), Eq(Node::TYPE_INTEGER) );
    ASSERT_THAT( operand2->type(), Eq(Node::TYPE_VAR_REF) );
}


TEST_F( TestParser, recognizesParenthesisInExpression )
{
    Node *node = parser.parse("(123+x)*(456-y)");
    ASSERT_THAT( node->type(), Eq(Node::TYPE_MUL) );
    NodeMul *nodeMul = dynamic_cast<NodeMul*>(node);
    Node *operand1 = nodeMul->operand1();
    Node *operand2 = nodeMul->operand2();
    ASSERT_THAT( operand1->type(), Eq(Node::TYPE_ADD) );
    ASSERT_THAT( operand2->type(), Eq(Node::TYPE_SUB) );
}

TEST_F( TestParser, recognizesVarDecl )
{
    Node *node = parser.parse("var x = 123");
    ASSERT_THAT( node->type(), Eq(Node::TYPE_ASSIGN) );
}

TEST_F( TestParser, recognizesVarDeclWithExpression )
{
    Node *node = parser.parse("var x = 123*x+456/y");
    ASSERT_THAT( node->type(), Eq(Node::TYPE_ASSIGN) );
    NodeAssign *nodeAssign = dynamic_cast<NodeAssign *>(node);
    NodeVarDecl *var = nodeAssign->var();
    Node *value = nodeAssign->value();

    ASSERT_THAT( var->name(), StrEq("x") );
    ASSERT_THAT( value->type(), Eq(Node::TYPE_ADD) );
    NodeAdd *nodeAdd = dynamic_cast<NodeAdd*>(value);
    Node *operand1 = nodeAdd->operand1();
    Node *operand2 = nodeAdd->operand2();
    ASSERT_THAT( operand1->type(), Eq(Node::TYPE_MUL) );
    ASSERT_THAT( operand2->type(), Eq(Node::TYPE_DIV) );
}
