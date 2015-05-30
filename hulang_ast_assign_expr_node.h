#ifndef INCLUDED_HULANG_AST_ASSIGN_EXPR_NODE_H
#define INCLUDED_HULANG_AST_ASSIGN_EXPR_NODE_H

#include <hulang_ast_expr_node.h>
#include <hulang_token_type.h>
#include <memory>

namespace hulang {

class AstAssignExprNode: public AstExprNode
{
public:
    // TYPES
    typedef std::unique_ptr<AstAssignExprNode> UP;
    typedef std::shared_ptr<AstAssignExprNode> SP;
    
private:
    // DATA
    TokenType::Value d_op;
    AstExprNode::SP  d_lhs;
    AstExprNode::SP  d_rhs;
    
private:
    // NOT IMPLEMENTED
    AstAssignExprNode(const AstAssignExprNode& other);
    AstAssignExprNode& operator= (const AstAssignExprNode& rhs);        

public:
    // CLASS METHODS
    static bool isValidTokenType(TokenType::Value op);
    
    // CREATORS
    AstAssignExprNode(TokenType::Value op,
                      AstExprNode::SP lhs,
                      AstExprNode::SP rhs);
    virtual ~AstAssignExprNode();

    // ACCESSORS
    virtual std::ostream&
    print(std::ostream& out, const Indenter& indenter) const;
};

} // close namespace hulang

#endif // INCLUDED_HULANG_AST_ASSIGN_EXPR_NODE_H
