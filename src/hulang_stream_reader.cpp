#include <hulang_stream_reader.h>
#include <cassert>

namespace hulang {

std::size_t StreamReader::read(char* buf, std::size_t maxSize)
{
    assert(buf);

    std::size_t cnt = 0;
    while(!eos() && cnt < maxSize)
    {
        buf[cnt++] = *d_it++;
    }

    return cnt;
}
    
} // close namespace hulang
