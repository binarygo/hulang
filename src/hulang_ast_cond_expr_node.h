#ifndef INCLUDED_HULANG_AST_COND_EXPR_NODE_H
#define INCLUDED_HULANG_AST_COND_EXPR_NODE_H

#include <hulang_ast_expr_node.h>
#include <memory>

namespace hulang {

class AstCondExprNode: public AstExprNode
{
public:
    // TYPES
    typedef std::unique_ptr<AstCondExprNode> UP;
    typedef std::shared_ptr<AstCondExprNode> SP;
    
private:
    // DATA
    AstExprNode::SP d_pred;
    AstExprNode::SP d_choice1;
    AstExprNode::SP d_choice2;

private:
    // NOT IMPLEMENTED
    AstCondExprNode(const AstCondExprNode& other);
    AstCondExprNode& operator= (const AstCondExprNode& rhs);        

public:
    // CREATORS
    AstCondExprNode(AstExprNode::SP pred,
                    AstExprNode::SP choice1,
                    AstExprNode::SP choice2);
    virtual ~AstCondExprNode();

    // ACCESSORS
    virtual std::ostream&
    print(std::ostream& out, const Indenter& indenter) const;
};

} // close namespace hulang

#endif // INCLUDED_HULANG_AST_COND_EXPR_NODE_H
