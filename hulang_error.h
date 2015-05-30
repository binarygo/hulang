#ifndef INCLUDED_HULANG_ERROR_H
#define INCLUDED_HULANG_ERROR_H

#include <exception>
#include <sstream>
#include <string>

namespace hulang {

class Error: public std::exception
{
private:
    // DATA
    std::string d_msg;
    
public:
    // CREATORS
    explicit Error(const std::string& msg): d_msg(msg) {}
    ~Error() {}
    Error(const Error& other): std::exception(other), d_msg(other.d_msg) {}

    // MANIPULATORS
    Error& operator= (const Error& rhs)
    {
        std::exception::operator=(rhs);
        if(this != &rhs)
        {
            d_msg = rhs.d_msg;
        }
        return *this;
    }

    std::string& msg() noexcept { return d_msg; }

    // ACCESSORS
    const std::string& msg() const noexcept { return d_msg; }
    const char* what() const noexcept { return d_msg.c_str(); }
};

#define THROW_HULANG_ERROR(msg)\
    do {\
        std::ostringstream hulang_error_oss;\
        hulang_error_oss << msg;\
        throw Error(hulang_error_oss.str());\
    } while(0)

} // close namespace hulang

#endif // INCLUDED_HULANG_ERROR_H
