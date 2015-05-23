#include <hulang_indenter.h>

namespace hulang {

// CREATORS
Indenter::Indenter(std::size_t lvl, std::size_t pad)
    : d_lvl(lvl)
    , d_pad(pad)
{
}

Indenter::~Indenter()
{
}

Indenter::Indenter(const Indenter& other)
    : d_lvl(other.d_lvl)
    , d_pad(other.d_pad)
{
}

// MANIPULATORS
Indenter& Indenter::operator= (const Indenter& rhs)
{
    if(this != &rhs)
    {
        d_lvl = rhs.d_lvl;
        d_pad = rhs.d_pad;
    }
    return *this;
}

// ACCESSORS
std::ostream& Indenter::print(std::ostream& out) const
{
    out << std::string(d_lvl*d_pad, ' ');
    return out;
}

std::ostream& operator<< (std::ostream& out, const Indenter& rhs)
{
    return rhs.print(out);
}
    
} // close namespace hulang
