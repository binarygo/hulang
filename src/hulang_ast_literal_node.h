#ifndef INCLUDED_HULANG_AST_LITERAL_NODE_H
#define INCLUDED_HULANG_AST_LITERAL_NODE_H

#include <hulang_ast_expr_node.h>
#include <hulang_token_type.h>
#include <memory>
#include <string>

namespace hulang {

class AstLiteralNode: public AstExprNode
{
public:
    // TYPES
    typedef std::unique_ptr<AstLiteralNode> UP;
    typedef std::shared_ptr<AstLiteralNode> SP;
    
private:
    // DATA
    TokenType::Value d_type;
    std::string      d_literal;

public:
    // CLASS METHODS
    static bool isValidTokenType(TokenType::Value type);
    
    // CREATORS
    AstLiteralNode(TokenType::Value type,
                   const std::string& literal);
    virtual ~AstLiteralNode();
    AstLiteralNode(const AstLiteralNode& other);

    // MANIPULATORS
    AstLiteralNode& operator= (const AstLiteralNode& rhs);

    TokenType::Value& type() { return d_type; }
    std::string& literal() { return d_literal; }
    
    // ACCESSORS
    TokenType::Value type() const { return d_type; }
    const std::string& literal() const { return d_literal; }

    virtual std::ostream&
    print(std::ostream& out, const Indenter& indenter) const;
};

} // close namespace hulang

#endif // INCLUDED_HULANG_AST_LITERAL_NODE_H
