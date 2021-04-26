#ifndef __darkness_io_header__
#define __darkness_io_header__

typedef uint32_t uchar;

/// printf is not thread safe, so we need our own impletation
extern int darkPrintf(const uchar* format, ...);

#endif //__darkness_io_header__
