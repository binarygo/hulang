#ifndef INCLUDED_HULANG_AST_POSTFIX_EXPR_NODE_H
#define INCLUDED_HULANG_AST_POSTFIX_EXPR_NODE_H

#include <hulang_ast_expr_node.h>
#include <hulang_token_type.h>
#include <memory>

namespace hulang {

class AstPostfixExprNode: public AstExprNode
{
public:
    // TYPES
    typedef std::unique_ptr<AstPostfixExprNode> UP;
    typedef std::shared_ptr<AstPostfixExprNode> SP;
    
private:
    // DATA
    TokenType::Value d_op;
    AstExprNode::SP  d_operand;
    
private:
    // NOT IMPLEMENTED
    AstPostfixExprNode(const AstPostfixExprNode& other);
    AstPostfixExprNode& operator= (const AstPostfixExprNode& rhs);        

public:
    // CLASS METHODS
    static bool isValidTokenType(TokenType::Value op);
    
    // CREATORS
    AstPostfixExprNode(TokenType::Value op,
                       AstExprNode::SP operand);
    virtual ~AstPostfixExprNode();

    // ACCESSORS
    virtual std::ostream&
    print(std::ostream& out, const Indenter& indenter) const;
};

} // close namespace hulang

#endif // INCLUDED_HULANG_AST_POSTFIX_EXPR_NODE_H
