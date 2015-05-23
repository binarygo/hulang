#include <hulang_lexer_marker.h>

namespace hulang {

// CREATORS
LexerMarker::LexerMarker(Lexer::Iter* it)
    : d_it(it)
{
    if(d_it) d_itSave = *d_it;
}

LexerMarker::~LexerMarker()
{
}

LexerMarker::LexerMarker(const LexerMarker& other)
    : d_it(other.d_it)
    , d_itSave(other.d_itSave)
{
}

LexerMarker& LexerMarker::operator= (const LexerMarker& rhs)
{
    if(this != &rhs)
    {
        d_it = rhs.d_it;
        d_itSave = rhs.d_itSave;
    }
    return *this;
}
    
void LexerMarker::rewind()
{
    if(d_it) *d_it = d_itSave;
}
    
} // close namespace hulang
