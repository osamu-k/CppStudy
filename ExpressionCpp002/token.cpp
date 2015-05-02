#include "token.h"

Token::Token( string s, Type type )
    :m_string(s),m_type(type)
{

}

Token::~Token()
{

}

Token::Type Token::type() const
{
    return m_type;
}

TokenInteger::TokenInteger( string s, int value )
    : Token(s,TYPE_INTEGER),m_value(value)
{

}

TokenInteger::~TokenInteger()
{

}

int TokenInteger::value()
{
    return m_value;
}

TokenName::TokenName( string s, string name )
    :Token(s,TYPE_NAME),m_name(name)
{

}

TokenName::~TokenName()
{

}

string TokenName::name()
{
    return m_name;
}

//TokenOperatorAdd::TokenOperatorAdd()
//    :Token(TYPE_OPERATOR_ADD)
//{

//}

//TokenOperatorAdd::~TokenOperatorAdd()
//{

//}

//TokenOperatorSub::TokenOperatorSub()
//    :Token(TYPE_OPERATOR_SUB)
//{

//}

//TokenOperatorSub::~TokenOperatorSub()
//{

//}

//TokenOperatorMul::TokenOperatorMul()
//    :Token(TYPE_OPERATOR_MUL)
//{

//}

//TokenOperatorMul::~TokenOperatorMul()
//{

//}

//TokenOperatorDiv::TokenOperatorDiv()
//    :Token(TYPE_OPERATOR_DIV)
//{

//}

//TokenOperatorDiv::~TokenOperatorDiv()
//{

//}

//TokenAssignment::TokenAssignment()
//    :Token(TYPE_ASSIGNMENT)
//{

//}

//TokenAssignment::~TokenAssignment()
//{

//}

//TokenParenLeft::TokenParenLeft()
//    :Token(TYPE_PAREN_LEFT)
//{

//}

//TokenParenLeft::~TokenParenLeft()
//{

//}

//TokenParenRight::TokenParenRight()
//    :Token(TYPE_PAREN_RIGHT)
//{

//}

//TokenParenRight::~TokenParenRight()
//{

//}
