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
        TYPE_NAME,
        TYPE_OPERATOR_ADD,
        TYPE_OPERATOR_SUB,
        TYPE_OPERATOR_MUL,
        TYPE_OPERATOR_DIV,
        TYPE_ASSIGNMENT,
        TYPE_PAREN_OPEN,
        TYPE_PAREN_CLOSE,
        TYPE_KEYWORD_VAR,
        TYPE_END
    };

    Token( string s = "", Type type = TYPE_UNDEFINED);
    virtual ~Token();
    Type type() const;
    void setString( string s )
    { m_string = s; }
    string getString()
    { return m_string; }

private:
    Type m_type;
    string m_string;
};

class TokenInteger : public Token
{
public:
    TokenInteger( string s ="", int value = 0 );
    ~TokenInteger();
    int value();
private:
    int m_value;
};

class TokenName : public Token
{
public:
    TokenName( string s = "", string name = "" );
    ~TokenName();
    string name();
private:
    string m_name;
};

#endif // TOKEN_H
