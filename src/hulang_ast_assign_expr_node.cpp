#include <hulang_ast_assign_expr_node.h>
#include <hulang_token_type.h>
#include <cassert>

namespace hulang {

// CLASS METHODS
bool AstAssignExprNode::isValidTokenType(TokenType::Value op)
{
    return
        op == TokenType::ASSIGN ||
        op == TokenType::PLUS_ASSIGN ||
        op == TokenType::MINUS_ASSIGN ||
        op == TokenType::MULTIPLY_ASSIGN ||
        op == TokenType::DIVIDE_ASSIGN ||
        op == TokenType::MOD_ASSIGN;
}
    
// CREATORS
AstAssignExprNode::AstAssignExprNode(TokenType::Value op,
                                     AstExprNode::SP lhs,
                                     AstExprNode::SP rhs)
    : d_op(op)
    , d_lhs(lhs)
    , d_rhs(rhs)
{
    assert(isValidTokenType(d_op) && d_lhs && d_rhs);
}

AstAssignExprNode::~AstAssignExprNode()
{
}

// ACCESSORS
std::ostream&
AstAssignExprNode::print(std::ostream& out, const Indenter& indenter) const
{
    out << indenter
        << "[ AssignExpr ]: " << TokenType::toString(d_op)
        << std::endl;
    d_lhs->print(out, indenter.nextLvl());
    d_rhs->print(out, indenter.nextLvl());
    return out;
}

} // close namespace hulang
