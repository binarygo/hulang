#ifndef INCLUDED_HULANG_AST_UNARY_EXPR_NODE_H
#define INCLUDED_HULANG_AST_UNARY_EXPR_NODE_H

#include <hulang_ast_expr_node.h>
#include <hulang_token_type.h>
#include <memory>

namespace hulang {

class AstUnaryExprNode: public AstExprNode
{
public:
    // TYPES
    typedef std::unique_ptr<AstUnaryExprNode> UP;
    typedef std::shared_ptr<AstUnaryExprNode> SP;
    
private:
    // DATA
    TokenType::Value d_op;
    AstExprNode::SP  d_operand;
    
private:
    // NOT IMPLEMENTED
    AstUnaryExprNode(const AstUnaryExprNode& other);
    AstUnaryExprNode& operator= (const AstUnaryExprNode& rhs);        

public:
    // CLASS METHODS
    static bool isValidTokenType(TokenType::Value op);
    
    // CREATORS
    AstUnaryExprNode(TokenType::Value op,
                     AstExprNode::SP operand);
    virtual ~AstUnaryExprNode();

    // ACCESSORS
    virtual std::ostream&
    print(std::ostream& out, const Indenter& indenter) const;
};

} // close namespace hulang

#endif // INCLUDED_HULANG_AST_UNARY_EXPR_NODE_H
