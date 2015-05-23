#include <hulang_token.h>

namespace hulang {

// CREATORS
Token::Token(TokenType::Value type, const std::string& lexeme)
    : d_type(type)
    , d_lexeme(lexeme)
{
}

Token::~Token()
{
}

Token::Token(const Token& other)
    : d_type(other.d_type)
    , d_lexeme(other.d_lexeme)
{
}

// MANIPULATORS
Token& Token::operator= (const Token& rhs)
{
    if(this != &rhs)
    {
        d_type = rhs.d_type;
        d_lexeme = rhs.d_lexeme;
    }
    return *this;
}

// ACCESSORS
bool Token::operator== (const Token& rhs) const
{
    return d_type == rhs.d_type && d_lexeme == rhs.d_lexeme;
}

bool Token::operator!= (const Token& rhs) const
{
    return !(operator==(rhs));
}
    
std::ostream& Token::print(std::ostream& out) const
{
    out << "("
        << TokenType::toString(d_type) << ","
        << "'" << d_lexeme << "'"
        << ")";
    return out;
}
    
} // close namespace hulang
