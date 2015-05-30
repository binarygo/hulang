#ifndef INCLUDED_HULANG_LEXER_MARKER_H
#define INCLUDED_HULANG_LEXER_MARKER_H

#include <hulang_lexer.h>
#include <string>

namespace hulang {

class LexerMarker
{
private:
    // DATA
    Lexer::Iter* d_it;
    Lexer::Iter d_itSave;

public:
    // CREATORS
    explicit LexerMarker(Lexer::Iter* it);
    ~LexerMarker();
    LexerMarker(const LexerMarker& other);

    // MANIPULATORS
    LexerMarker& operator= (const LexerMarker& rhs);
    void rewind();
};

} // close namespace hulang

#endif // INCLUDED_HULANG_LEXER_MARKER_H
