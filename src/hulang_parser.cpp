#include <hulang_parser.h>
#include <hulang_error.h>
#include <hulang_util.h>
#include <hulang_ast_node.h>
#include <hulang_ast_expr_node.h>
#include <hulang_ast_assign_expr_node.h>
#include <hulang_ast_cond_expr_node.h>
#include <hulang_ast_logic_expr_node.h>
#include <hulang_ast_arithmetic_expr_node.h>
#include <hulang_ast_unary_expr_node.h>
#include <hulang_ast_postfix_expr_node.h>
#include <hulang_ast_id_node.h>
#include <hulang_ast_literal_node.h>
#include <iostream>
#include <sstream>

namespace hulang {

namespace {

std::string slineno(int lineno)
{
    std::ostringstream oss;
    oss << "L" << lineno << ": ";
    return oss.str();
}
    
} // close anonymous namespace
    
// CREATORS
Parser::Parser(std::istream& in)
    : d_streamReader(in)
    , d_lexer(&d_streamReader)
    , d_it(d_lexer.begin())
{
}

Parser::~Parser()
{
}

// ACCESSORS
int Parser::getLineno() const
{
    return d_it.lineno();
}

// MANIPULATORS
LexerMarker Parser::mark()
{
    return LexerMarker(&d_it);
}
    
bool Parser::test(TokenType::Value tokenType, bool must)
{
    return test(0, tokenType, must);
}
    
bool Parser::test(TokenType::Value* t, TokenType::Value tokenType, bool must)
{   
    if(tokenType == d_it.token().type())
    {
        ++d_it;
        if(t) *t = tokenType;
        return true;
    }
    if(must)
    {
        THROW_HULANG_ERROR(
            slineno(d_it.lineno()) <<
            "unexpect token " << d_it.token() << ", " <<
            "expect " << TokenType::toString(tokenType) << "\n");
    }
    return false;
}

// MACROS
#define PRE_PARSE \
    int entering_lineno = getLineno(); \
    try {
    
#define POST_PARSE(TERMINAL) \
    } catch(Error& e) {\
        e.msg() = slineno(entering_lineno) + #TERMINAL + "\n" + e.msg(); \
        throw; \
    } \
    return false

// MANIPULATORS
bool Parser::prog(AstNode::SP& ans, bool must)
{
    PRE_PARSE;

    LexerMarker marker = mark();
    
    AstExprNode::SP exprNode;
    if(expr(exprNode, must) &&
       test(TokenType::EOS, must))
    {
        ans = exprNode;
        return true;
    }

    marker.rewind();
    return false;
    
    POST_PARSE(prog);
}
        
bool Parser::expr(AstExprNode::SP& ans, bool must)
{
    PRE_PARSE;

    return assignExpr(ans, must);

    POST_PARSE(expr);
}

bool Parser::assignExpr(AstExprNode::SP& ans, bool must)
{
    PRE_PARSE;
    
    if(!condExpr(ans, must)) return false;

    LexerMarker marker = mark();

    TokenType::Value op = TokenType::ERROR;
    AstExprNode::SP exprNode;
    if((test(&op, TokenType::ASSIGN, false) ||
        test(&op, TokenType::PLUS_ASSIGN, false) ||
        test(&op, TokenType::MINUS_ASSIGN, false) ||
        test(&op, TokenType::MULTIPLY_ASSIGN, false) ||
        test(&op, TokenType::MOD_ASSIGN, false) ||
        test(&op, TokenType::DIVIDE_ASSIGN, false))
       &&
       assignExpr(exprNode, false))
    {
        ans = std::make_shared<AstAssignExprNode>(op, ans, exprNode);
        assert(ans);
    }
    else
    {
        marker.rewind();
    }
    return true;

    POST_PARSE(assignExpr);
}
    
bool Parser::condExpr(AstExprNode::SP& ans, bool must)
{
    PRE_PARSE;
    
    if(!orExpr(ans, must)) return false;

    while(true)
    {
        LexerMarker marker = mark();

        AstExprNode::SP expr1;
        AstExprNode::SP expr2;
        if(test(TokenType::QMARK, false) &&
           expr(expr1, false) &&
           test(TokenType::COLON, false) &&
           orExpr(expr2, false))
        {
            ans = std::make_shared<AstCondExprNode>(ans, expr1, expr2);
            assert(ans);
        }
        else
        {
            marker.rewind();
            break;
        }
    }
    return true;
    
    POST_PARSE(condExpr);
}
    
bool Parser::orExpr(AstExprNode::SP& ans, bool must)
{
    PRE_PARSE;

    if(!andExpr(ans, must)) return false;

    while(true)
    {
        LexerMarker marker = mark();

        TokenType::Value op = TokenType::ERROR;
        AstExprNode::SP exprNode;
        if(test(&op, TokenType::OR, false)
           &&
           andExpr(exprNode, false))
        {
            ans = std::make_shared<AstLogicExprNode>(op, ans, exprNode);
            assert(ans);
        }
        else
        {
            marker.rewind();
            break;
        }
    }
    return true;

    POST_PARSE(orExpr);
}

bool Parser::andExpr(AstExprNode::SP& ans, bool must)
{
    PRE_PARSE;

    if(!eqExpr(ans, must)) return false;

    while(true)
    {
        LexerMarker marker = mark();

        TokenType::Value op = TokenType::ERROR;
        AstExprNode::SP exprNode;
        if(test(&op, TokenType::AND, false)
           &&
           eqExpr(exprNode, false))
        {
            ans = std::make_shared<AstLogicExprNode>(op, ans, exprNode);
            assert(ans);
        }
        else
        {
            marker.rewind();
            break;
        }
    }
    return true;
    
    POST_PARSE(andExpr);
}

bool Parser::eqExpr(AstExprNode::SP& ans, bool must)
{
    PRE_PARSE;

    if(!relExpr(ans, must)) return false;

    while(true)
    {
        LexerMarker marker = mark();

        TokenType::Value op = TokenType::ERROR;
        AstExprNode::SP exprNode;
        if((test(&op, TokenType::EQ, false) ||
            test(&op, TokenType::NE, false))
           &&
           relExpr(exprNode, false))
        {
            ans = std::make_shared<AstArithmeticExprNode>(op, ans, exprNode);
            assert(ans);
        }   
        else
        {
            marker.rewind();
            break;
        }
    }
    return true;

    POST_PARSE(eqExpr);
}

bool Parser::relExpr(AstExprNode::SP& ans, bool must)
{
    PRE_PARSE;

    if(!addExpr(ans, must)) return false;

    while(true)
    {
        LexerMarker marker = mark();

        TokenType::Value op = TokenType::ERROR;
        AstExprNode::SP exprNode;
        if((test(&op, TokenType::LT, false) ||
            test(&op, TokenType::GT, false) ||
            test(&op, TokenType::LE, false) ||
            test(&op, TokenType::GE, false))
           &&
           addExpr(exprNode, false))
        {
            ans = std::make_shared<AstArithmeticExprNode>(op, ans, exprNode);
            assert(ans);
        }
        else
        {
            marker.rewind();
            break;
        }
    }
    return true;
    
    POST_PARSE(relExpr);
}
    
bool Parser::addExpr(AstExprNode::SP& ans, bool must)
{
    PRE_PARSE;
    
    if(!multiplyExpr(ans, must)) return false;

    while(true)
    {
        LexerMarker marker = mark();

        TokenType::Value op = TokenType::ERROR;
        AstExprNode::SP exprNode;
        if((test(&op, TokenType::PLUS, false) ||
            test(&op, TokenType::MINUS, false))
           &&
           multiplyExpr(exprNode, false))
        {
            ans = std::make_shared<AstArithmeticExprNode>(op, ans, exprNode);
            assert(ans);
        }
        else
        {
            marker.rewind();
            break;
        }
    }
    return true;

    POST_PARSE(addExpr);
}

bool Parser::multiplyExpr(AstExprNode::SP& ans, bool must)
{
    PRE_PARSE;
    
    if(!powerExpr(ans, must)) return false;

    while(true)
    {
        LexerMarker marker = mark();

        TokenType::Value op = TokenType::ERROR;
        AstExprNode::SP exprNode;
        if((test(&op, TokenType::MULTIPLY, false) ||
            test(&op, TokenType::DIVIDE, false) ||
            test(&op, TokenType::MOD, false))
           &&
           powerExpr(exprNode, false))
        {
            ans = std::make_shared<AstArithmeticExprNode>(op, ans, exprNode);
            assert(ans);
        }
        else
        {
            marker.rewind();
            break;
        }
    }
    return true;
    
    POST_PARSE(multiplyExpr);
}

bool Parser::powerExpr(AstExprNode::SP& ans, bool must)
{
    PRE_PARSE;
    
    if(!unaryExpr(ans, must)) return false;

    LexerMarker marker = mark();

    TokenType::Value op = TokenType::ERROR;
    AstExprNode::SP exprNode;
    if(test(&op, TokenType::POWER, false)
       &&
       powerExpr(exprNode, false))
    {
        ans = std::make_shared<AstArithmeticExprNode>(op, ans, exprNode);
        assert(ans);
    }
    else
    {
        marker.rewind();
    }
    return true;

    POST_PARSE(powerExpr);
}

bool Parser::unaryExpr(AstExprNode::SP& ans, bool must)
{
    PRE_PARSE;
    
    if(postfixExpr(ans, false)) return true;

    LexerMarker marker = mark();
    
    TokenType::Value op = TokenType::ERROR;
    AstExprNode::SP exprNode;
    if((test(&op, TokenType::PLUS, false) ||
        test(&op, TokenType::MINUS, false) ||
        test(&op, TokenType::NOT, false) ||
        test(&op, TokenType::INC, false) ||
        test(&op, TokenType::DEC, must))
       &&
       unaryExpr(exprNode, must))
    {
        if(op == TokenType::PLUS)
        {
            ans = exprNode;
        }
        else
        {
            ans = std::make_shared<AstUnaryExprNode>(op, exprNode);
        }
        assert(ans);
        return true;
    }

    marker.rewind();
    return false;

    POST_PARSE(unaryExpr);
}

bool Parser::postfixExpr(AstExprNode::SP& ans, bool must)
{
    PRE_PARSE;

    if(!primaryExpr(ans, must)) return false;

    while(true)
    {
        LexerMarker marker = mark();

        TokenType::Value op = TokenType::ERROR;
        if(test(&op, TokenType::INC, false) ||
           test(&op, TokenType::DEC, false))
        {
            ans = std::make_shared<AstPostfixExprNode>(op, ans);
            assert(ans);
        }
        else
        {
            marker.rewind();
            break;
        }
    }
    return true;
    
    POST_PARSE(postfixExpr);
}
    
bool Parser::primaryExpr(AstExprNode::SP& ans, bool must)
{
    PRE_PARSE;
    
    LexerMarker marker = mark();

    TokenType::Value type = TokenType::ERROR;
    if(test(&type, TokenType::ID, false))
    {
        ans =
            std::make_shared<AstIdNode>(
                (d_it-1).token().lexeme());
        return true;
    }
    else if(test(&type, TokenType::INTEGER, false) ||
            test(&type, TokenType::FLOAT, false))
    {
        ans =
            std::make_shared< AstLiteralNode >(
                type,
                (d_it-1).token().lexeme());
        return true;
    }
    else if(test(TokenType::LPAR, must) &&
            expr(ans, must) &&
            test(TokenType::RPAR, must))
    {
        return true;
    }
    
    marker.rewind();
    return false;

    POST_PARSE(primaryExpr);
}

bool Parser::parse(AstNode::SP& ans)
{
    return prog(ans, true);
}

} // close namespace hulang
