#include <hulang_ast_logic_expr_node.h>
#include <hulang_token_type.h>
#include <cassert>

namespace hulang {

// CLASS METHODS
bool AstLogicExprNode::isValidTokenType(TokenType::Value op)
{
    return
        op == TokenType::AND ||
        op == TokenType::OR;
}
    
// CREATORS
AstLogicExprNode::AstLogicExprNode(TokenType::Value op,
                                   AstExprNode::SP operand1,
                                   AstExprNode::SP operand2)
    : d_op(op)
    , d_operand1(operand1)
    , d_operand2(operand2)
{
    assert(isValidTokenType(d_op) && d_operand1 && d_operand2);
}

AstLogicExprNode::~AstLogicExprNode()
{
}

// ACCESSORS
std::ostream&
AstLogicExprNode::print(std::ostream& out, const Indenter& indenter) const
{
    out << indenter
        << "[ LogicExpr ]: " << TokenType::toString(d_op)
        << std::endl;
    d_operand1->print(out, indenter.nextLvl());
    d_operand2->print(out, indenter.nextLvl());
    return out;
}

} // close namespace hulang
