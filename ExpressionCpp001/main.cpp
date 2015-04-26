#include "gmock/gmock.h"

#include <ctype.h>
#include <string.h>
#include <list>
#include <map>

#include "evaluater.h"
#include "node.h"
#include "parser.h"
//#include "token.h"
#include "tokenizer.h"
#include "nodevisitor.h"
using namespace std;
using namespace testing;

TEST( Tokenizer, canRecognizesNumber )
{
    Tokenizer tokenizer;
    tokenizer.setSource( "12345" );
    Token token = tokenizer.next();
    ASSERT_THAT( token.type(), Eq(Token::TYPE_INTEGER) );
    ASSERT_THAT( token.text(), StrEq("12345") );
}

TEST( Tokenizer, canSkipSpaces )
{
    Tokenizer tokenizer;
    tokenizer.setSource( " \t \n 12345" );
    Token token = tokenizer.next();
    ASSERT_THAT( token.type(), Eq(Token::TYPE_INTEGER) );
    ASSERT_THAT( token.text(), StrEq("12345") );
}

TEST( Tokenizer, canRecognizesName )
{
    Tokenizer tokenizer;
    tokenizer.setSource( "azAZ09" );
    Token token = tokenizer.next();
    ASSERT_THAT( token.type(), Eq(Token::TYPE_NAME) );
    ASSERT_THAT( token.text(), StrEq("azAZ09") );
}

TEST( Tokenizer, canRecognizesKeywordVar )
{
    Tokenizer tokenizer;
    tokenizer.setSource( "var" );
    Token token = tokenizer.next();
    ASSERT_THAT( token.type(), Eq(Token::TYPE_KEY_VAR) );
    ASSERT_THAT( token.text(), StrEq("var") );
}

TEST( Tokenizer, canRecognizesOpAdd )
{
    Tokenizer tokenizer;
    tokenizer.setSource( "+" );
    Token token = tokenizer.next();
    ASSERT_THAT( token.type(), Eq(Token::TYPE_OP_ADD_SUB) );
    ASSERT_THAT( token.text(), StrEq("+") );
}

TEST( Tokenizer, canRecognizesOpSub )
{
    Tokenizer tokenizer;
    tokenizer.setSource( "-" );
    Token token = tokenizer.next();
    ASSERT_THAT( token.type(), Eq(Token::TYPE_OP_ADD_SUB) );
    ASSERT_THAT( token.text(), StrEq("-") );
}

TEST( Tokenizer, canRecognizesOpMul )
{
    Tokenizer tokenizer;
    tokenizer.setSource( "*" );
    Token token = tokenizer.next();
    ASSERT_THAT( token.type(), Eq(Token::TYPE_OP_MUL_DIV) );
    ASSERT_THAT( token.text(), StrEq("*") );
}

TEST( Tokenizer, canRecognizesOpDiv )
{
    Tokenizer tokenizer;
    tokenizer.setSource( "*" );
    Token token = tokenizer.next();
    ASSERT_THAT( token.type(), Eq(Token::TYPE_OP_MUL_DIV) );
    ASSERT_THAT( token.text(), StrEq("*") );
}

TEST( Tokenizer, canRecognizesEqual )
{
    Tokenizer tokenizer;
    tokenizer.setSource( "=" );
    Token token = tokenizer.next();
    ASSERT_THAT( token.type(), Eq(Token::TYPE_EQUAL) );
    ASSERT_THAT( token.text(), StrEq("=") );
}

TEST( Parser, canParseInteger )
{
    Tokenizer tokenizer;
    Parser parser( &tokenizer );
    parser.setSource("12345");
    Node *node = parser.parse();

    NodeInteger *inode = dynamic_cast<NodeInteger *>(node);
    ASSERT_THAT( inode, Ne(static_cast<NodeInteger*>(0)) );
    ASSERT_THAT( inode->value(), Eq(12345) );
}

TEST( Parser, canParseAssignment )
{
    Tokenizer tokenizer;
    Parser parser( &tokenizer );
    parser.setSource("var abc=12345");
    Node *node = parser.parse();

    NodeAssign *anode = dynamic_cast<NodeAssign *>(node);
    ASSERT_THAT( anode, Ne(static_cast<NodeAssign*>(0)) );
}

TEST( Parser, evalueateInteger )
{
    Tokenizer tokenizer;
    Parser parser( &tokenizer );
    Evaluater evaluater( &parser );
    string expression = "12345";
    ASSERT_THAT( evaluater.evaluate( expression ), Eq(12345) );
}

TEST( Parser, evalueateAddition )
{
    Tokenizer tokenizer;
    Parser parser( &tokenizer );
    Evaluater evaluater( &parser );
    string expression = "12345+6789";
    ASSERT_THAT( evaluater.evaluate( expression ), Eq(12345+6789) );
}

TEST( Parser, evalueateSubtraction )
{
    Tokenizer tokenizer;
    Parser parser( &tokenizer );
    Evaluater evaluater( &parser );
    string expression = "12345-6789";
    ASSERT_THAT( evaluater.evaluate( expression ), Eq(12345-6789) );
}

TEST( Parser, evalueateMultiplication )
{
    Tokenizer tokenizer;
    Parser parser( &tokenizer );
    Evaluater evaluater( &parser );
    string expression = "12345*6789";
    ASSERT_THAT( evaluater.evaluate( expression ), Eq(12345*6789) );
}

TEST( Parser, evalueateDivision )
{
    Tokenizer tokenizer;
    Parser parser( &tokenizer );
    Evaluater evaluater( &parser );
    string expression = "12345/67";
    ASSERT_THAT( evaluater.evaluate( expression ), Eq(12345/67) );
}

TEST( Parser, evalueateComplexExpression )
{
    Tokenizer tokenizer;
    Parser parser( &tokenizer );
    Evaluater evaluater( &parser );
    string expression = "123+45*678-90/12";
    ASSERT_THAT( evaluater.evaluate( expression ), Eq(123+45*678-90/12) );
}


TEST( Parser, evalueateExpressionWithParenthesis )
{
    Tokenizer tokenizer;
    Parser parser( &tokenizer );
    Evaluater evaluater( &parser );
    string expression = "(123+45)*(678-90)/12";
    ASSERT_THAT( evaluater.evaluate( expression ), Eq((123+45)*(678-90)/12) );
}

TEST( Parser, evalueateExpressionWithParenthesis2 )
{
    Tokenizer tokenizer;
    Parser parser( &tokenizer );
    Evaluater evaluater( &parser );
    string expression = "((123+45)*((678-90)/12))";
    ASSERT_THAT( evaluater.evaluate( expression ), Eq(((123+45)*((678-90)/12))) );
}

TEST( Parser, assignmentStoresVariable )
{
    Tokenizer tokenizer;
    Parser parser( &tokenizer );
    Evaluater evaluater( &parser );
    ASSERT_THAT( evaluater.evaluate( "var x=123" ), Eq(123) );
    ASSERT_THAT( evaluater.evaluate( "var y=456" ), Eq(456) );
    ASSERT_THAT( evaluater.evaluate( "x" ), Eq(123) );
    ASSERT_THAT( evaluater.evaluate( "y" ), Eq(456) );
    ASSERT_THAT( evaluater.evaluate( "x+y" ), Eq(123+456) );
}

TEST( Parser, evalueateExpressionWithParenthesis3 )
{
    Tokenizer tokenizer;
    Parser parser( &tokenizer );
    NodeVisitor visitor;
    string expression = "((123+45)*((678-90)/12))";
    parser.setSource( expression );
    Node *node = parser.parse();
    node->visit( &visitor );
    ASSERT_THAT( visitor.value(), Eq(((123+45)*((678-90)/12))) );
}

TEST( Parser, assignmentStoresVariable2 )
{
    Tokenizer tokenizer;
    Parser parser( &tokenizer );
    NodeVisitor visitor;
    parser.setSource( "var x=123" );
    Node *node = parser.parse();
    node->visit( &visitor );
    ASSERT_THAT( visitor.value(), Eq(123) );

    parser.setSource( "var y=456" );
    node = parser.parse();
    node->visit( &visitor );
    ASSERT_THAT( visitor.value(), Eq(456) );

    parser.setSource( "x+y" );
    node = parser.parse();
    node->visit( &visitor );
    ASSERT_THAT( visitor.value(), Eq(123+456) );
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleMock(&argc,argv);
    return RUN_ALL_TESTS();
}
