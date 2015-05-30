#include <hulang_ast_unary_expr_node.h>
#include <cassert>

namespace hulang {

// CLASS METHODS
bool AstUnaryExprNode::isValidTokenType(TokenType::Value op)
{
    return
        op == TokenType::PLUS ||
        op == TokenType::MINUS ||
        op == TokenType::NOT ||
        op == TokenType::INC ||
        op == TokenType::DEC;
}
    
// CREATORS
AstUnaryExprNode::AstUnaryExprNode(TokenType::Value op,
                                   AstExprNode::SP operand)
    : d_op(op)
    , d_operand(operand)
{
    assert(isValidTokenType(d_op) && d_operand);
}

AstUnaryExprNode::~AstUnaryExprNode()
{
}

// ACCESSORS
std::ostream&
AstUnaryExprNode::print(std::ostream& out, const Indenter& indenter) const
{
    out << indenter
        << "[ UnaryExpr ]: " << TokenType::toString(d_op)
        << std::endl;
    d_operand->print(out, indenter.nextLvl());
    return out;
}

} // close namespace hulang
