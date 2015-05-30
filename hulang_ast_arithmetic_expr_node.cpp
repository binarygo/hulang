#include <hulang_ast_arithmetic_expr_node.h>
#include <cassert>

namespace hulang {

// CLASS METHODS
bool AstArithmeticExprNode::isValidTokenType(TokenType::Value op)
{
    return
        op == TokenType::LT ||
        op == TokenType::GT ||
        op == TokenType::LE ||
        op == TokenType::GE ||
        op == TokenType::EQ ||
        op == TokenType::NE ||
        op == TokenType::PLUS ||
        op == TokenType::MINUS ||
        op == TokenType::MULTIPLY ||
        op == TokenType::DIVIDE ||
        op == TokenType::MOD ||
        op == TokenType::POWER;
}
    
// CREATORS
AstArithmeticExprNode::AstArithmeticExprNode(TokenType::Value op,
                                             AstExprNode::SP operand1,
                                             AstExprNode::SP operand2)
    : d_op(op)
    , d_operand1(operand1)
    , d_operand2(operand2)
{
    assert(isValidTokenType(d_op) && d_operand1 && d_operand2);
}

AstArithmeticExprNode::~AstArithmeticExprNode()
{
}

// ACCESSORS
std::ostream&
AstArithmeticExprNode::print(std::ostream& out, const Indenter& indenter) const
{
    out << indenter
        << "[ ArithmeticExpr ]: " << TokenType::toString(d_op)
        << std::endl;
    d_operand1->print(out, indenter.nextLvl());
    d_operand2->print(out, indenter.nextLvl());
    return out;
}
    
} // close namespace hulang
