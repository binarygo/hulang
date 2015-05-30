#ifndef INCLUDED_HULANG_AST_LOGIC_EXPR_NODE_H
#define INCLUDED_HULANG_AST_LOGIC_EXPR_NODE_H

#include <hulang_ast_expr_node.h>
#include <hulang_token_type.h>
#include <memory>

namespace hulang {

class AstLogicExprNode: public AstExprNode
{
public:
    // TYPES
    typedef std::unique_ptr<AstLogicExprNode> UP;
    typedef std::shared_ptr<AstLogicExprNode> SP;
    
private:
    // DATA
    TokenType::Value d_op;
    AstExprNode::SP  d_operand1;
    AstExprNode::SP  d_operand2;

private:
    // NOT IMPLEMENTED
    AstLogicExprNode(const AstLogicExprNode& other);
    AstLogicExprNode& operator= (const AstLogicExprNode& rhs);        

public:
    // CLASS METHODS
    static bool isValidTokenType(TokenType::Value op);
    
    // CREATORS
    AstLogicExprNode(TokenType::Value op,
                     AstExprNode::SP operand1,
                     AstExprNode::SP operand2);
    virtual ~AstLogicExprNode();

    // ACCESSORS
    virtual std::ostream&
    print(std::ostream& out, const Indenter& indenter) const;
};

} // close namespace hulang

#endif // INCLUDED_HULANG_AST_LOGIC_EXPR_NODE_H
