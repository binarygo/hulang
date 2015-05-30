#ifndef INCLUDED_HULANG_AST_EXPR_NODE_H
#define INCLUDED_HULANG_AST_EXPR_NODE_H

#include <hulang_ast_node.h>
#include <memory>
#include <string>

namespace hulang {

class AstExprNode: public AstNode
{
public:
    // TYPES
    typedef std::unique_ptr<AstExprNode> UP;
    typedef std::shared_ptr<AstExprNode> SP;
    
public:
    // CREATORS
    virtual ~AstExprNode() {}

    // ACCESSORS
    virtual std::ostream&
    print(std::ostream& out, const Indenter& indenter) const = 0;
};

} // close namespace hulang

#endif // INCLUDED_HULANG_AST_EXPR_NODE_H
