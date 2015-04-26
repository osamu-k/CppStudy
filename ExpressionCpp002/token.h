#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using namespace std;

class Token
{
public:

    enum Type{
        TYPE_UNDEFINED,
        TYPE_INTEGER,
        TYPE_VARIABLE,
        TYPE_OPERATOR_ADD,
        TYPE_OPERATOR_SUB,
        TYPE_OPERATOR_MUL,
        TYPE_OPERATOR_DIV,
        TYPE_ASSIGNMENT,
        TYPE_PAREN_LEFT,
        TYPE_PAREN_RIGHT
    };

    Token( Type type = TYPE_UNDEFINED);
    virtual ~Token();
    Type type() const;

private:
    Type m_type;
};

class TokenInteger : public Token
{
public:
    TokenInteger( int value );
    ~TokenInteger();
    int value();
private:
    int m_value;
};

class TokenVariable : public Token
{
public:
    TokenVariable( string name );
    ~TokenVariable();
    string name();
private:
    string m_name;
};

class TokenOperatorAdd: public Token
{
public:
    TokenOperatorAdd();
    ~TokenOperatorAdd();
};

class TokenOperatorSub: public Token
{
public:
    TokenOperatorSub();
    ~TokenOperatorSub();
};

class TokenOperatorMul: public Token
{
public:
    TokenOperatorMul();
    ~TokenOperatorMul();
};

class TokenOperatorDiv: public Token
{
public:
    TokenOperatorDiv();
    ~TokenOperatorDiv();
};

class TokenAssignment: public Token
{
public:
    TokenAssignment();
    ~TokenAssignment();
};

class TokenParenLeft: public Token
{
public:
    TokenParenLeft();
    ~TokenParenLeft();
};

class TokenParenRight: public Token
{
public:
    TokenParenRight();
    ~TokenParenRight();
};

#endif // TOKEN_H
