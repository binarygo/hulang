#include <hulang_ast_cond_expr_node.h>
#include <cassert>

namespace hulang {

// CREATORS
AstCondExprNode::AstCondExprNode(AstExprNode::SP pred,
                                 AstExprNode::SP choice1,
                                 AstExprNode::SP choice2)
    : d_pred(pred)
    , d_choice1(choice1)
    , d_choice2(choice2)
{
    assert(d_pred && d_choice1 && d_choice2);
}

AstCondExprNode::~AstCondExprNode()
{
}

// ACCESSORS
std::ostream&
AstCondExprNode::print(std::ostream& out, const Indenter& indenter) const
{
    out << indenter << "[ COND ]" << std::endl;
    d_pred->print(out, indenter.nextLvl());
    d_choice1->print(out, indenter.nextLvl());
    d_choice2->print(out, indenter.nextLvl());
    return out;
}

} // close namespace hulang
