#ifndef INCLUDED_HULANG_PARSER_H
#define INCLUDED_HULANG_PARSER_H

#include <hulang_lexer.h>
#include <hulang_lexer_marker.h>
#include <hulang_ast_node.h>
#include <hulang_ast_expr_node.h>
#include <string>
#include <iostream>
#include <sstream>

namespace hulang {

class Parser
{
private:
    // DATA
    StreamReader d_streamReader;
    Lexer        d_lexer;
    Lexer::Iter  d_it;
    
private:
    // NOT IMPLEMENTED
    Parser(const Parser& other);
    Parser& operator= (const Parser& rhs);        

    // ACCESSORS
    int getLineno() const;
    
    // MANIPULATORS
    LexerMarker mark();
    bool test(TokenType::Value tokenType, bool must);
    bool test(TokenType::Value* t, TokenType::Value tokenType, bool must);
    
    /*
      expr <- assign_expr
      assign_expr <- cond_expr (("="|"+="|"-="|"*="|"/=") assign_expr)?
      cond_expr <- or_expr ("?" expr ":" or_expr)*
      or_expr <- and_expr ("||" and_expr)*
      and_expr <- eq_expr ("&&" eq_expr)*
      eq_expr <- rel_expr (("=="|"!=") rel_expr)*
      rel_expr <- add_expr (("<"|">"|"<="|">=") add_expr)*
      add_expr <- multiply_expr (("+"|"-") multiply_expr)*
      multiply_expr <- power_expr (("*"|"/") power_expr)*
      power_expr <- unary_expr ("^" power_expr)?
      unary_expr <- postfix_expr
                  / ("+"|"-"|"!"|"++"|"--") unary_expr
      postfix_expr <- primary_expr ("++"|"--")*
      primary_expr <- ID | INTEGER | FLOAT | STRING | "(" expr ")"
     */
    // MANIPULATORS
    bool prog(AstNode::SP& ans, bool must);
    bool expr(AstExprNode::SP& ans, bool must);
    bool assignExpr(AstExprNode::SP& ans, bool must);
    bool condExpr(AstExprNode::SP& ans, bool must);
    bool orExpr(AstExprNode::SP& ans, bool must);
    bool andExpr(AstExprNode::SP& ans, bool must);
    bool eqExpr(AstExprNode::SP& ans, bool must);
    bool relExpr(AstExprNode::SP& ans, bool must);
    bool addExpr(AstExprNode::SP& ans, bool must);
    bool multiplyExpr(AstExprNode::SP& ans, bool must);
    bool powerExpr(AstExprNode::SP& ans, bool must);
    bool unaryExpr(AstExprNode::SP& ans, bool must);
    bool postfixExpr(AstExprNode::SP& ans, bool must);
    bool primaryExpr(AstExprNode::SP& ans, bool must);

public:
    // CREATORS
    Parser(std::istream& in);
    ~Parser();

    // MAINPULATORS
    bool parse(AstNode::SP& ans);
};

} // close namespace hulang

#endif // INCLUDED_HULANG_PARSER_H
