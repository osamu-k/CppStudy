#ifndef EVALUATER_H
#define EVALUATER_H

#include <map>
#include <string>

using namespace std;

class Node;
class Parser;

class Evaluater
{
public:
    Evaluater( Parser *parser )
        :m_parser(parser)
    {
    }

    ~Evaluater()
    {
    }

    int evaluate( string expression );

private:
    int evaluateNode( Node *node );
    Parser *m_parser;
    map<string,int> m_context;
};

#endif // EVALUATER_H
