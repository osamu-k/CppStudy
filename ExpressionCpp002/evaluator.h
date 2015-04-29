#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "node.h"
#include "nodevisitor.h"
#include "parser.h"

#include <map>
#include <stack>
using namespace std;

class Evaluator : public NodeVisitor
{
public:
    Evaluator( Parser *parser )
        :m_parser(parser)
    {}

    ~Evaluator()
    {}

    int evaluate( string source )
    {
        Node *node = m_parser->parse( source );
        node->acceptVisitor( this );
        int value = m_valueStack.top();
        m_valueStack.pop();
        return value;
    }

    void visit( NodeInteger *node )
    {
        m_valueStack.push( node->value() );
    }
    void visit( NodeAdd *node )
    {
        int operand2 = m_valueStack.top();
        m_valueStack.pop();
        int operand1 = m_valueStack.top();
        m_valueStack.pop();
        m_valueStack.push( operand1 + operand2 );
    }
    void visit( NodeSub *node )
    {
        int operand2 = m_valueStack.top();
        m_valueStack.pop();
        int operand1 = m_valueStack.top();
        m_valueStack.pop();
        m_valueStack.push( operand1 - operand2 );
    }
    void visit( NodeMul *node )
    {
        int operand2 = m_valueStack.top();
        m_valueStack.pop();
        int operand1 = m_valueStack.top();
        m_valueStack.pop();
        m_valueStack.push( operand1 * operand2 );
    }
    void visit( NodeDiv *node )
    {
        int operand2 = m_valueStack.top();
        m_valueStack.pop();
        int operand1 = m_valueStack.top();
        m_valueStack.pop();
        m_valueStack.push( operand1 / operand2 );
    }
    void visit( NodePlus *node )
    {
        // Nothing to do.
    }
    void visit( NodeMinus *node )
    {
        int value = m_valueStack.top();
        m_valueStack.pop();
        m_valueStack.push( - value );
    }
    void visit( NodeVarDecl *node )
    {
        m_varName = node->name();
    }
    void visit( NodeVarRef *node )
    {
        m_valueStack.push(m_varMap[node->name()]);
    }
    void visit( NodeAssign *node )
    {
        m_varMap[m_varName] = m_valueStack.top();
    }

private:
    Parser *m_parser;
    stack<int> m_valueStack;
    string m_varName;
    map<string,int> m_varMap;
};

#endif // EVALUATOR_H
