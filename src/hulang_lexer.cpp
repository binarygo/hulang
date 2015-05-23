#include <hulang_lexer.h>
#include <hulang_error.h>
#include <hulang_token.h>
#include <hulang_token_type.h>
#include <cassert>

extern "C" {
#include <hulang_flex_lexer.h>
}
    
namespace hulang {

// CREATORS
Lexer::Iter::Iter()
    : d_lexer(0)
    , d_pos(0)
{
}
    
Lexer::Iter::Iter(Lexer& lexer, int pos)
    : d_lexer(&lexer)
    , d_pos(0)
{
    set(pos);
}

// MANIPULATORS
void Lexer::Iter::set(int newpos)
{
    checkNotNull();
    
    if(newpos >= 0)
    {
        int sz = d_lexer->size();
        for(int i = 0, n = newpos-sz+1; i < n; ++i)
        {
            if(!d_lexer->next())
            {
                d_pos = -1;
                return;
            }
        }
        int maxPos = d_lexer->size()-1;
        d_pos = newpos > maxPos ? maxPos : newpos;
    }
    else
    {
        d_pos = -1;
    }
}

// ACCESSORS
void Lexer::Iter::checkNotNull() const
{
    if(!d_lexer)
    {
        THROW_HULANG_ERROR("Lexer::Iter: null iterator");
    }
}
    
void Lexer::Iter::checkNotEnd() const
{
    checkNotNull();
    
    assert(d_pos == -1 || (d_pos >= 0 && d_pos < d_lexer->size()));
    if(d_pos == -1)
    {
        THROW_HULANG_ERROR("Lexer::Iter: end of token stream");
    }
}

// CREATORS
Lexer::Iter::Iter(const Iter& other)
    : d_lexer(other.d_lexer)
    , d_pos(other.d_pos)
{
}
    
Lexer::Iter::~Iter()
{
}

// MANIPULATORS
Lexer::Iter& Lexer::Iter::operator= (const Iter& rhs)
{
    if(this != &rhs)
    {
        d_lexer = rhs.d_lexer;
        d_pos = rhs.d_pos;
    }
    return *this;
}

Lexer::Iter& Lexer::Iter::operator++()
{
    advance(1);
    return *this;
}

Lexer::Iter Lexer::Iter::operator++(int)
{
    Iter ans(*this);
    advance(1);
    return ans;
}

Lexer::Iter& Lexer::Iter::operator--()
{
    advance(-1);
    return *this;
}

Lexer::Iter Lexer::Iter::operator--(int)
{
    Iter ans(*this);
    advance(-1);
    return ans;
}

Lexer::Iter& Lexer::Iter::operator+=(int diff)
{
    advance(diff);
    return *this;
}
    
Lexer::Iter& Lexer::Iter::operator-=(int diff)
{
    advance(-diff);
    return *this;
}
        
void Lexer::Iter::advance(int diff)
{
    checkNotNull();
    
    if(d_pos < 0)
    {
        if(diff >= 0) return;
        else
        {
            while(d_lexer->next()) ;
            d_pos = int(d_lexer->size())+diff;
            if(d_pos <= 0) d_pos = 0;
        }
    }
    else
    {
        d_pos += diff;
        if(d_pos <= 0) d_pos = 0;
        set(d_pos);
    }
}

// ACCESSORS
bool Lexer::Iter::operator== (const Iter& rhs) const
{
    return d_lexer == rhs.d_lexer && d_pos == rhs.d_pos;
}

bool Lexer::Iter::operator!= (const Iter& rhs) const
{
    return !(operator==(rhs));
}
    
const Token& Lexer::Iter::token() const
{
    checkNotEnd();
    return d_lexer->extTokens()[d_pos].first;
}

int Lexer::Iter::lineno() const
{
    checkNotEnd();
    return d_lexer->extTokens()[d_pos].second;
}

Lexer::Iter operator+(const Lexer::Iter& lhs, int rhs)
{
    Lexer::Iter ans(lhs);
    ans += rhs;
    return ans;
}

Lexer::Iter operator+(int lhs, const Lexer::Iter& rhs)
{
    return operator+(rhs, lhs);
}

Lexer::Iter operator-(const Lexer::Iter& lhs, int rhs)
{
    return operator+(lhs, -rhs);
}
    
Lexer::Iter operator-(int lhs, const Lexer::Iter& rhs)
{
    return operator-(rhs, lhs);
}
    
///////////////////////////////////////////////////////////////////////////////
    
// CREATORS
Lexer::Lexer(StreamReader* streamReader)
    : d_streamReader(streamReader)
    , d_scanner(0)
{
    assert(d_streamReader);
    
    init();
}

Lexer::~Lexer()
{
    destroy();
}

// MANIPULATORS
void Lexer::init()
{
    if(0 != hulang_yylex_init_extra((void*)d_streamReader, &d_scanner) ||
       0 == d_scanner)
    {
        THROW_HULANG_ERROR("fail to initialize lexer");
    }    
} 

void Lexer::destroy()
{
    if(d_scanner)
    {
        hulang_yylex_destroy(d_scanner);
    }
    d_scanner = 0;
}
    
bool Lexer::next()
{
    if(0 == d_scanner)
    {
        return false;
    }

    TokenType::Value tokenType;
    bool ok = TokenType::fromInt(&tokenType, hulang_yylex(d_scanner));
    assert(ok);

    int lineno = hulang_yyget_lineno(d_scanner);
    
    if(TokenType::EOS != tokenType)
    {
        char* text = hulang_yyget_text(d_scanner);
        std::size_t sz = hulang_yyget_leng(d_scanner);
        std::string lexeme(text, sz);
        
        if(TokenType::ERROR != tokenType)
        {
            d_extTokens.push_back(ExtToken(Token(tokenType, lexeme), lineno));
        }
        else
        {
            destroy();
            THROW_HULANG_ERROR("unexpected lexeme: " << lexeme);
        }
    }
    else
    {
        d_extTokens.push_back(ExtToken(Token(tokenType, ""), lineno));
        destroy();
    }
    
    return true;
}
    
} // close namespace hulang
