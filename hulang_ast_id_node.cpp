#include <hulang_ast_id_node.h>

namespace hulang {

// CREATORS
AstIdNode::AstIdNode(const std::string& name)
    : d_name(name)
{
}

AstIdNode::AstIdNode(const AstIdNode& other)
    : d_name(other.d_name)
{
}

// MANIPULATORS
AstIdNode& AstIdNode::operator= (const AstIdNode& rhs)
{
    if(this != &rhs)
    {
        d_name = rhs.d_name;
    }
    return *this;
}

// ACCESSORS
std::ostream& AstIdNode::
print(std::ostream& out, const Indenter& indenter) const
{
    out << indenter << "[ ID ] " << d_name << std::endl;
    return out;
}
    
} // close namespace hulang
