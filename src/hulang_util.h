#ifndef INCLUDED_HULANG_UTIL_H
#define INCLUDED_HULANG_UTIL_H

#include <hulang_error.h>
#include <sstream>
#include <string>

namespace hulang {

struct Util
{
    template<typename T>
    static
    T parse(const std::string& s)
    {
        std::istringstream iss(s);
        T t;
        iss >> t;
        if(iss.fail())
        {
            THROW_HULANG_ERROR("failed to parse '" << s << "'");
        }
        return t;
    }
};

} // close namespace hulang

#endif // INCLUDED_HULANG_UTIL_H
