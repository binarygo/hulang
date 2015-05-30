#ifndef INCLUDED_HULANG_STREAM_READER_H
#define INCLUDED_HULANG_STREAM_READER_H

#include <iostream>
#include <iterator>

namespace hulang {

class StreamReader
{
private:
    // DATA
    std::istreambuf_iterator<char> d_it;
    std::istreambuf_iterator<char> d_eos;

private:
    // NOT IMPLEMENTED
    StreamReader(const StreamReader& other);
    StreamReader& operator= (const StreamReader& rhs);
    
public:
    // CREATORS
    StreamReader(std::istream& in): d_it(in) {}
    ~StreamReader() {}

    // MANIPULATORS
    std::size_t read(char* buf, std::size_t maxSize);

    // ACCESSORS
    bool eos() const { return d_it == d_eos; }
};
    
} // close namespace hulang

#endif // INCLUDED_HULANG_STREAM_READER_H
