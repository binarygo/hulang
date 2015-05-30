#ifndef INCLUDED_HULANG_TOKEN_H
#define INCLUDED_HULANG_TOKEN_H

#include <hulang_token_type.h>
#include <string>
#include <vector>
#include <iostream>

namespace hulang {

class Token
{
public:
    // TYPES
    typedef std::vector<Token> Vector;
    
private:
    // DATA
    TokenType::Value d_type;
    std::string      d_lexeme;
    
public:
    // CREATORS
    Token(TokenType::Value type, const std::string& lexeme);
    ~Token();
    Token(const Token& other);

    // MANIPULATORS
    Token& operator= (const Token& rhs);

    TokenType::Value& type() { return d_type; }
    std::string& lexeme() { return d_lexeme; }

    // ACCESSORS
    bool operator== (const Token& rhs) const;
    bool operator!= (const Token& rhs) const;
    
    TokenType::Value type() const { return d_type; }
    const std::string& lexeme() const { return d_lexeme; }

    std::ostream& print(std::ostream& out) const;
};

///////////////////////////////////////////////////////////////////////////////

inline std::ostream& operator<< (std::ostream& out, const Token& rhs)
{
    return rhs.print(out);
}

} // close namespace hulang

#endif // INCLUDED_HULANG_TOKEN_H
