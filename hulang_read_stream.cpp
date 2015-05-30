#include <hulang_read_stream.h>
#include <hulang_stream_reader.h>

#include <stdexcept>
#include <cassert>

extern "C"
size_t hulang_read_stream(char* buf, size_t max_size, void* stream_reader)
{
    assert(stream_reader);

    try
    {
        hulang::StreamReader* streamReader = (hulang::StreamReader*)stream_reader;
        return streamReader->read(buf, max_size);
    }
    catch(...)
    {
        // no-op
    }

    return 0;
}
