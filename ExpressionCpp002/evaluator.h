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
    Evaluator()
        : m_error(false)
    {}

    ~Evaluator()
    {}

    int evaluate( Node *node ){
        m_error = false;
        m_errorMessage = "";

        if( node == 0 ){
            setError("No expression to evaluate.");
            return 0;
        }
        node->acceptVisitor( this );
        int value = 0;
        if( ! m_error ){
            value = popValue();
        }
        return value;
    }

    void visit( NodeInteger *node )
    {
        if( m_error ) return;
        m_valueStack.push( node->value() );
    }

    void visit( NodeAdd *node )
    {
        if( m_error ) return;

        int operand2 = 0;
        if( node->operand2() ){
            operand2 = popValue();
        }
        int operand1 = 0;
        if( node->operand1() ){
            operand1 = popValue();
        }
        m_valueStack.push( operand1 + operand2 );
    }

    void visit( NodeSub *node )
    {
        if( m_error ) return;

        int operand2 = 0;
        if( node->operand2() ){
            operand2 = popValue();
        }
        int operand1 = 0;
        if( node->operand1() ){
            operand1 = popValue();
        }
        m_valueStack.push( operand1 - operand2 );
    }

    void visit( NodeMul *node )
    {
        if( m_error ) return;

        int operand2 = 1;
        if( node->operand2() ){
            operand2 = popValue();
        }
        int operand1 = 1;
        if( node->operand1() ){
            operand1 = popValue();
        }
        m_valueStack.push( operand1 * operand2 );
    }

    void visit( NodeDiv *node )
    {
        if( m_error ) return;

        int operand2 = 1;
        if( node->operand2() ){
            operand2 = popValue();
        }
        int operand1 = 1;
        if( node->operand1() ){
            operand1 = popValue();
        }
        if( operand2 == 0 ){
            setError("Divided by zero.");
            return;
        }
        m_valueStack.push( operand1 / operand2 );
    }

    void visit( NodePlus *node )
    {
        if( m_error ) return;

        int operand = 0;
        if( node->operand() ){
            operand = popValue();
        }
        m_valueStack.push( operand );
    }

    void visit( NodeMinus *node )
    {
        if( m_error ) return;

        int operand = 0;
        if( node->operand() ){
            operand = popValue();
        }
        m_valueStack.push( - operand );
    }

    void visit( NodeVarDecl *node )
    {
        if( m_error ) return;

        m_varName = node->name();
    }

    void visit( NodeVarRef *node )
    {
        if( m_error ) return;

        if( m_varMap.find(node->name()) == m_varMap.end() ){
            setError("Variable '" + node->name() + "' is not defined.");
        }
        m_valueStack.push(m_varMap[node->name()]);
    }

    void visit( NodeAssign *node )
    {
        if( m_error ) return;

        int value = 0;
        if( node->value() ){
            value = m_valueStack.top();
        }
        m_varMap[m_varName] = value;
    }

    void setError( string message )
    {
        m_error = true;
        m_errorMessage = message;
    }

    bool isError()
    {
        return m_error;
    }

    string errorMessage()
    {
        return m_errorMessage;
    }

private:
    void pushValue( int value )
    {
        m_valueStack.push( value );
    }

    int popValue()
    {
        if( m_valueStack.empty() )
            return 0;
        int value = m_valueStack.top();
        m_valueStack.pop();
        return value;
    }

    stack<int> m_valueStack;
    string m_varName;
    map<string,int> m_varMap;
    bool m_error;
    string m_errorMessage;
};

#endif // EVALUATOR_H
