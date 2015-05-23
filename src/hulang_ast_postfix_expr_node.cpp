#include <hulang_ast_postfix_expr_node.h>
#include <cassert>

namespace hulang {

// CLASS METHODS
bool AstPostfixExprNode::isValidTokenType(TokenType::Value op)
{
    return
        op == TokenType::INC ||
        op == TokenType::DEC;
}
    
// CREATORS
AstPostfixExprNode::AstPostfixExprNode(TokenType::Value op,
                                       AstExprNode::SP operand)
    : d_op(op)
    , d_operand(operand)
{
    assert(isValidTokenType(d_op) && d_operand);
}

AstPostfixExprNode::~AstPostfixExprNode()
{
}

std::ostream&
AstPostfixExprNode::print(std::ostream& out, const Indenter& indenter) const
{
    out << indenter
        << "[ PostfixExpr ]: " << TokenType::toString(d_op)
        << std::endl;
    d_operand->print(out, indenter.nextLvl());
    return out;
}

} // close namespace hulang
