#ifndef INCLUDED_HULANG_READ_STREAM_H
#define INCLUDED_HULANG_READ_STREAM_H

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

size_t hulang_read_stream(char* buf, size_t max_size, void* stream_reader);

#ifdef __cplusplus
} // end extern "C"
#endif
    
#endif // INCLUDED_HULANG_READ_STREAM_H
