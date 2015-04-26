
#include "node.h"
#include "nodevisitor.h"

Node::Node( Type type )
    : m_type(type)
{
}

Node::~Node()
{
}

Node::Type Node::type()
{
    return m_type;
}

