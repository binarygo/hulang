#ifndef INCLUDED_HULANG_AST_ID_NODE_H
#define INCLUDED_HULANG_AST_ID_NODE_H

#include <hulang_ast_expr_node.h>
#include <memory>
#include <string>

namespace hulang {

class AstIdNode: public AstExprNode
{
public:
    // TYPES
    typedef std::unique_ptr<AstIdNode> UP;
    typedef std::shared_ptr<AstIdNode> SP;
    
private:
    // DATA
    std::string d_name;
    
public:
    // CREATORS
    explicit AstIdNode(const std::string& name);
    virtual ~AstIdNode() {}
    AstIdNode(const AstIdNode& other);
    
    // MANIPULATORS
    AstIdNode& operator= (const AstIdNode& rhs);

    std::string& name() { return d_name; }
    
    // ACCESSORS
    const std::string name() const { return d_name; }

    virtual std::ostream&
    print(std::ostream& out, const Indenter& indenter) const;
};

} // close namespace hulang

#endif // INCLUDED_HULANG_AST_ID_NODE_H
