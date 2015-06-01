#include <hulang_peg_parser.h>
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
#include <yapeg_any.h>
#include <yapeg_combinators.h>
#include <iostream>
#include <sstream>

namespace hulang {

// CREATORS
PegParser::PegParser(std::istream& in)
    : d_streamReader(in)
    , d_lexer(&d_streamReader)
{
}

PegParser::~PegParser()
{
}

namespace {

class S
{
private:
    // DATA
    Lexer& d_lexer;
    Lexer::Iter d_lexerIt;

    yapeg::Any d_cache;
    
private:
    // NOT IMPLEMENTED
    S(const S& other);
    S& operator=(const S& rhs);
    
public:    
    // CREATORS
    S(Lexer& lexer)
        : d_lexer(lexer)
        , d_lexerIt(d_lexer.begin())
    {
    }

    // MANIPULATORS
    void setPos(Lexer::Iter lexerIt)
    {
        d_lexerIt = lexerIt;
    }

    Lexer::Iter& lexerIt()
    {
        return d_lexerIt;
    }

    yapeg::Any& cache()
    {
        return d_cache;
    }
    
    // ACCESSORS
    Lexer::Iter getPos() const
    {
        return d_lexerIt;
    }
};

// FUNCTIONS
std::string slineno(int lineno)
{
    std::ostringstream oss;
    oss << "L" << lineno << ": ";
    return oss.str();
}
    
yapeg::Parser<S> baseParser(TokenType::Value tokenType)
{
    auto p =
        [tokenType](S& s, bool must)->yapeg::RCode
        {
            if(tokenType == s.lexerIt().token().type())
            {
                s.cache().set(s.lexerIt().token());
                ++s.lexerIt();
                return yapeg::RCode::SUCCESS;
            }
            if(must)
            {
                THROW_HULANG_ERROR(
                    slineno(s.lexerIt().lineno()) <<
                    "unexpect token " << s.lexerIt().token() << ", " <<
                    "expect " << TokenType::toString(tokenType) << "\n");
            }
            return yapeg::RCode::FAIL;
        };
    return yapeg::normalize<S>(p);
}

/*  PEG RULES
    expr <- assign_expr
    assign_expr <- cond_expr (("="|"+="|"-="|"*="|"/=") assign_expr)?
    cond_expr <- or_expr ("?" expr ":" or_expr)*
    or_expr <- and_expr ("||" and_expr)*
    and_expr <- eq_expr ("&&" eq_expr)*
    eq_expr <- rel_expr (("=="|"!=") rel_expr)*
    rel_expr <- add_expr (("<"|">"|"<="|">=") add_expr)*
    add_expr <- multiply_expr (("+"|"-") multiply_expr)*
    multiply_expr <- power_expr (("*"|"/"|"%") power_expr)*
    power_expr <- unary_expr ("^" power_expr)?
    unary_expr <- postfix_expr
                  / ("+"|"-"|"!"|"++"|"--") unary_expr
    postfix_expr <- primary_expr ("++"|"--")*
    primary_expr <- ID | INTEGER | FLOAT | STRING | "(" expr ")"
*/

yapeg::RCode prog(S& s, bool must);
yapeg::RCode expr(S& s, bool must);
yapeg::RCode assignExpr(S& s, bool must);
yapeg::RCode condExpr(S& s, bool must);
yapeg::RCode orExpr(S& s, bool must);
yapeg::RCode andExpr(S& s, bool must);
yapeg::RCode eqExpr(S& s, bool must);
yapeg::RCode relExpr(S& s, bool must);
yapeg::RCode addExpr(S& s, bool must);
yapeg::RCode multiplyExpr(S& s, bool must);
yapeg::RCode powerExpr(S& s, bool must);
yapeg::RCode unaryExpr(S& s, bool must);
yapeg::RCode postfixExpr(S& s, bool must);
yapeg::RCode primaryExpr(S& s, bool must);

// MACROS
#define PRE_PARSE(TERMINAL) \
    int entering_lineno = s.lexerIt().lineno(); \
    try {

#define POST_PARSE(TERMINAL) \
    } catch(Error& e) {\
        e.msg() = slineno(entering_lineno) + #TERMINAL + "\n" + e.msg(); \
        throw; \
    } \
    return yapeg::RCode::FAIL

// FUNCTIONS
template<typename AstNodeType>
yapeg::RCode rightAssocExprImpl(yapeg::Parser<S> lhsExpr,
                                yapeg::Parser<S> termExpr,
                                const std::vector<TokenType::Value>& ops,
                                S& s,
                                bool must)
{
    // A -> term (op A)?

    AstExprNode::SP ans;
    TokenType::Value op = TokenType::ERROR;

    std::vector< yapeg::Parser<S> > opExprs;
    opExprs.reserve(ops.size());
    for(auto it: ops) opExprs.push_back(baseParser(it));

    auto p =
        yapeg::seq<S>({
            termExpr,
            yapeg::yaction<S>(yapeg::capture<S, AstExprNode::SP>(ans)),
            yapeg::qmark<S>(
                yapeg::seq<S>({
                    yapeg::choice<S>(
                        opExprs,
                        [&op](S& s) { op = s.cache().get<Token>().type(); }
                    ),
                    lhsExpr,
                    yapeg::yaction<S>(
                        [&ans, &op](S& s) {
                            ans = std::make_shared<AstNodeType>(
                                op, ans, s.cache().get<AstExprNode::SP>());
                        }
                    )                        
                })
            )
        });

    return yapeg::invoke(p, s, must, ans);
}
    
template<typename AstNodeType>
yapeg::RCode leftAssocExprImpl(yapeg::Parser<S> termExpr,
                               const std::vector<TokenType::Value>& ops,
                               S& s,
                               bool must)
{
    // A -> term (op term)*
    
    AstExprNode::SP ans;
    TokenType::Value op = TokenType::ERROR;

    std::vector< yapeg::Parser<S> > opExprs;
    opExprs.reserve(ops.size());
    for(auto it: ops) opExprs.push_back(baseParser(it));
    
    auto p =
        yapeg::seq<S>({
            termExpr,
            yapeg::yaction<S>(yapeg::capture<S, AstExprNode::SP>(ans)),
            yapeg::star<S>(
                yapeg::seq<S>({
                    yapeg::choice<S>(
                        opExprs,
                        [&op](S& s) { op = s.cache().get<Token>().type(); }
                    ),
                    termExpr,
                    yapeg::yaction<S>(
                        [&ans, &op](S& s) {
                            ans = std::make_shared<AstNodeType>(
                                op, ans, s.cache().get<AstExprNode::SP>());
                        }
                    )
                })
            )
        });

    return invoke(p, s, must, ans);
}

yapeg::RCode prog(S& s, bool must)
{
    PRE_PARSE(prog);

    AstNode::SP ans;
    auto p =
        yapeg::seq<S>({
            expr,
            yapeg::yaction<S>(yapeg::capture<S, AstExprNode::SP>(ans)),
            baseParser(TokenType::EOS)
        });
    return yapeg::invoke(p, s, must, ans);

    POST_PARSE(prog);
}
    
yapeg::RCode expr(S& s, bool must)
{
    PRE_PARSE(expr);

    return assignExpr(s, must);

    POST_PARSE(expr);
}

yapeg::RCode assignExpr(S& s, bool must)
{
    PRE_PARSE(assignExpr);

    return rightAssocExprImpl<AstAssignExprNode>(
        assignExpr,
        condExpr,
        {
            TokenType::ASSIGN,
            TokenType::PLUS_ASSIGN,
            TokenType::MINUS_ASSIGN,
            TokenType::MULTIPLY_ASSIGN,
            TokenType::MOD_ASSIGN,
            TokenType::DIVIDE_ASSIGN
        }, s, must);    
        
    POST_PARSE(assignExpr);
}

yapeg::RCode condExpr(S& s, bool must)
{
    PRE_PARSE(condExpr);

    AstExprNode::SP ans;
    AstExprNode::SP tmp;
    
    auto p =
        yapeg::seq<S>({
            orExpr,
            yapeg::yaction<S>(yapeg::capture<S, AstExprNode::SP>(ans)),
            yapeg::star<S>(
                yapeg::seq<S>({
                    baseParser(TokenType::QMARK),
                    expr,
                    yapeg::yaction<S>(yapeg::capture<S, AstExprNode::SP>(tmp)),
                    baseParser(TokenType::COLON),
                    orExpr,
                    yapeg::yaction<S>(
                        [&ans, &tmp](S& s) {
                            ans = std::make_shared<AstCondExprNode>(
                                ans, tmp, s.cache().get<AstExprNode::SP>());
                        }
                    )
                })
            )
        });

    return yapeg::invoke(p, s, must, ans);
    
    POST_PARSE(condExpr);
}

yapeg::RCode orExpr(S& s, bool must)
{
    PRE_PARSE(orExpr);

    return leftAssocExprImpl<AstLogicExprNode>(
        andExpr, { TokenType::OR }, s, must);
    
    POST_PARSE(orExpr);
}

yapeg::RCode andExpr(S& s, bool must)
{
    PRE_PARSE(andExpr);

    return leftAssocExprImpl<AstLogicExprNode>(
        eqExpr, { TokenType::AND }, s, must);
    
    POST_PARSE(andExpr);
}

yapeg::RCode eqExpr(S& s, bool must)
{
    PRE_PARSE(eqExpr);

    return leftAssocExprImpl<AstArithmeticExprNode>(
        relExpr,
        {
            TokenType::EQ,
            TokenType::NE
        }, s, must);
    
    POST_PARSE(eqExpr);
}

yapeg::RCode relExpr(S& s, bool must)
{
    PRE_PARSE(relExpr);

    return leftAssocExprImpl<AstArithmeticExprNode>(
        addExpr,
        {
            TokenType::LT,
            TokenType::GT,
            TokenType::LE,
            TokenType::GE
        }, s, must);
    
    POST_PARSE(relExpr);    
}

yapeg::RCode addExpr(S& s, bool must)
{
    PRE_PARSE(addExpr);

    return leftAssocExprImpl<AstArithmeticExprNode>(
        multiplyExpr,
        {
            TokenType::PLUS,
            TokenType::MINUS
        }, s, must);
    
    POST_PARSE(addExpr);
}

yapeg::RCode multiplyExpr(S& s, bool must)
{
    PRE_PARSE(multiplyExpr);

    return leftAssocExprImpl<AstArithmeticExprNode>(
        powerExpr,
        {
            TokenType::MULTIPLY,
            TokenType::DIVIDE,
            TokenType::MOD
        }, s, must);
    
    POST_PARSE(multiplyExpr);    
}

yapeg::RCode powerExpr(S& s, bool must)
{
    PRE_PARSE(powerExpr);

    return rightAssocExprImpl<AstArithmeticExprNode>(
        powerExpr, unaryExpr, { TokenType::POWER }, s, must);
    
    POST_PARSE(powerExpr);
}

yapeg::RCode unaryExpr(S& s, bool must)
{
    PRE_PARSE(unaryExpr);

    AstExprNode::SP ans;
    TokenType::Value op = TokenType::ERROR;
    
    auto p =
        yapeg::choice<S>({
            yapeg::combo<S>(
                postfixExpr,
                yapeg::capture<S, AstExprNode::SP>(ans)
            ),
            yapeg::seq<S>({
                yapeg::choice<S>(
                    {
                        baseParser(TokenType::PLUS),
                        baseParser(TokenType::MINUS),
                        baseParser(TokenType::NOT),
                        baseParser(TokenType::INC),
                        baseParser(TokenType::DEC)    
                    },
                    [&op](S& s) {
                        op = s.cache().get<Token>().type();
                    }
                ),
                unaryExpr,
                yapeg::yaction<S>(
                    [&ans, &op](S& s) {
                        if(TokenType::PLUS == op)
                        {
                            ans = s.cache().get<AstExprNode::SP>();
                        }
                        else
                        {
                            ans = std::make_shared<AstUnaryExprNode>(
                                op, s.cache().get<AstExprNode::SP>());
                        }
                    }
                )
            })
        });

    return yapeg::invoke(p, s, must, ans);
    
    POST_PARSE(unaryExpr);
}

yapeg::RCode postfixExpr(S& s, bool must)
{
    PRE_PARSE(postfixExpr);

    AstExprNode::SP ans;
    
    auto p =
        yapeg::seq<S>({
            primaryExpr,
            yapeg::yaction<S>(yapeg::capture<S, AstExprNode::SP>(ans)),
            yapeg::star<S>(
                yapeg::choice<S>(
                    {
                        baseParser(TokenType::INC),
                        baseParser(TokenType::DEC)
                    },
                    [&ans](S& s) {
                        ans = std::make_shared<AstPostfixExprNode>(
                            s.cache().get<Token>().type(), ans);
                    }
                )
            )
        });

    return yapeg::invoke(p, s, must, ans);
    
    POST_PARSE(postfixExpr);
}

yapeg::RCode primaryExpr(S& s, bool must)
{
    PRE_PARSE(primaryExpr);

    AstExprNode::SP ans;
    
    auto p =
        yapeg::choice<S>({
            yapeg::combo<S>(
                baseParser(TokenType::ID),
                [&ans](S& s) {
                    ans = std::make_shared<AstIdNode>(s.cache().get<Token>().lexeme());
                }
            ),
            yapeg::choice<S>(
                {
                    baseParser(TokenType::INTEGER),
                    baseParser(TokenType::FLOAT),
                    baseParser(TokenType::STRING)
                },
                [&ans](S& s) {
                    ans = std::make_shared<AstLiteralNode>(
                        s.cache().get<Token>().type(),
                        s.cache().get<Token>().lexeme());
                }
            ),
            yapeg::seq<S>({
                baseParser(TokenType::LPAR),
                expr,
                yapeg::yaction<S>(yapeg::capture<S, AstExprNode::SP>(ans)),
                baseParser(TokenType::RPAR),
            })
        });
    
    return yapeg::invoke(p, s, must, ans);
    
    POST_PARSE(primaryExpr);
}
    
} // close anonymous namespace

// MANIPULATORS
AstNode::SP PegParser::parse()
{
    S s(d_lexer);

    yapeg::RCode rc = prog(s, true);
    if(yapeg::RCode::SUCCESS == rc)
    {
        return s.cache().get<AstNode::SP>();
    }

    return AstNode::SP();
}

} // close namespace hulang
