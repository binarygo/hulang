#include <hulang_ast_literal_node.h>
#include <cassert>

namespace hulang {

// CLASS METHODS
bool AstLiteralNode::isValidTokenType(TokenType::Value type)
{
    return
        type == TokenType::INTEGER ||
        type == TokenType::FLOAT;
}

// CREATORS
AstLiteralNode::AstLiteralNode(TokenType::Value type,
                               const std::string& literal)
    : d_type(type)
    , d_literal(literal)
{
    assert(isValidTokenType(d_type));
}

AstLiteralNode::~AstLiteralNode()
{
}

AstLiteralNode::AstLiteralNode(const AstLiteralNode& other)
    : d_type(other.d_type)
    , d_literal(other.d_literal)
{
}

// MANIPULATORS
AstLiteralNode& AstLiteralNode::operator= (const AstLiteralNode& rhs)
{
    if(this != &rhs)
    {
        d_type = rhs.d_type;
        d_literal = rhs.d_literal;
    }
    return *this;
}

// ACCESSORS
std::ostream&
AstLiteralNode::print(std::ostream& out, const Indenter& indenter) const
{
    out << indenter << "[ LITERAL ]: "
        << TokenType::toString(d_type) << "," << d_literal
        << std::endl;
    return out;
}
    
} // close namespace hulang
