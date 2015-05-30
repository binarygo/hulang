#ifndef INCLUDED_HULANG_LEXER_H
#define INCLUDED_HULANG_LEXER_H

#include <hulang_stream_reader.h>
#include <hulang_token.h>
#include <string>
#include <utility>
#include <vector>
#include <cassert>

namespace hulang {

class Lexer
{
public:
    // TYPES
    class Iter
    {
    private:
        // DATA
        Lexer* d_lexer;
        int    d_pos;

        // FRIENDS
        friend class Lexer;
        
    private:
        // CREATORS
        Iter(Lexer& lexer, int pos);

        // MANIPULATORS
        void set(int newpos);

        // ACCESSORS;
        void checkNotNull() const;
        void checkNotEnd() const;
        
    public:
        // CREATORS
        Iter();
        Iter(const Iter& other);
        ~Iter();

        // MANIPULATORS
        Iter& operator= (const Iter& rhs);

        Iter& operator++();
        Iter operator++(int);

        Iter& operator--();
        Iter operator--(int);

        Iter& operator+=(int diff);
        Iter& operator-=(int diff);
        
        void advance(int diff);

        // ACCESSORS
        bool operator== (const Iter& rhs) const;
        bool operator!= (const Iter& rhs) const;
        
        const Token& token() const;
        int lineno() const;
    };

public:
    // TYPES
    typedef std::pair<Token, int> ExtToken;
    typedef std::vector<ExtToken> ExtTokens;

private:
    // DATA
    StreamReader* d_streamReader;
    void*         d_scanner;
    ExtTokens     d_extTokens;
    
private:
    // NOT IMPLEMENTED
    Lexer(const Lexer& other);
    Lexer& operator= (const Lexer& rhs);        

    // MANIPULATORS
    void init();
    void destroy();
    
public:
    // CREATORS
    Lexer(StreamReader* streamReader);
    ~Lexer();

    // MANIPULATORS
    bool next();

    Iter begin() { return Iter(*this, 0); }
    Iter end() { return Iter(*this, -1); }
    
    // ACCESSORS
    std::size_t size() const { return d_extTokens.size(); }
    const ExtTokens& extTokens() const { return d_extTokens; }
};

Lexer::Iter operator+(const Lexer::Iter& lhs, int rhs);
Lexer::Iter operator+(int lhs, const Lexer::Iter& rhs);
Lexer::Iter operator-(const Lexer::Iter& lhs, int rhs);
Lexer::Iter operator-(int lhs, const Lexer::Iter& rhs);

} // close namespace hulang

#endif // INCLUDED_HULANG_LEXER_H
