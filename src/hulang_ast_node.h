#ifndef INCLUDED_HULANG_AST_NODE_H
#define INCLUDED_HULANG_AST_NODE_H

#include <hulang_indenter.h>

#include <memory>
#include <string>
#include <iostream>

namespace hulang {

class AstNode
{
public:
    // TYPES
    typedef std::unique_ptr<AstNode> UP;
    typedef std::shared_ptr<AstNode> SP;

public:
    // CREATORS
    virtual ~AstNode() {}

    // ACCESSORS
    virtual std::ostream&
    print(std::ostream& out, const Indenter& indenter) const = 0;
};

} // close namespace hulang

#endif // INCLUDED_HULANG_AST_NODE_H
