#ifndef INCLUDED_HULANG_INDENTER_H
#define INCLUDED_HULANG_INDENTER_H

#include <string>
#include <iostream>

namespace hulang {

class Indenter
{
private:
    std::size_t d_lvl;
    std::size_t d_pad;

public:
    // CREATORS
    Indenter(std::size_t lvl = 0, std::size_t pad = 2);
    ~Indenter();
    Indenter(const Indenter& other);

    // MANIPULATORS
    Indenter& operator= (const Indenter& rhs);

    std::size_t& lvl() { return d_lvl; }
    std::size_t& pad() { return d_pad; }
    
    // ACCESSORS
    std::size_t lvl() const { return d_lvl; }
    std::size_t pad() const { return d_pad; }
    Indenter nextLvl() const { return Indenter(d_lvl+1, d_pad); }
    
    std::ostream& print(std::ostream& out) const;
};

std::ostream& operator<< (std::ostream& out, const Indenter& rhs);

} // close namespace hulang

#endif // INCLUDED_HULANG_INDENTER_H
