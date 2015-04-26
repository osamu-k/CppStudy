#ifndef TOKEN_H
#define TOKEN_H

#include <string>
using namespace std;

class Token
{
public:
    enum Type {
        TYPE_UNDEFINED,
        TYPE_INTEGER,
        TYPE_NAME,
        TYPE_OP_ADD_SUB,
        TYPE_OP_MUL_DIV,
        TYPE_PAREN_LEFT,
        TYPE_PAREN_RIGHT,
        TYPE_EQUAL,
        TYPE_KEY_VAR,
        TYPE_END
    };

    Token( Type type = TYPE_UNDEFINED, string text = string() );
    Token( Type type, char c );
    ~Token();
    Token::Type type();
    string text();

private:
    Type m_type;
    string m_text;
};

#endif // TOKEN_H
