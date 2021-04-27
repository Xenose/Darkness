#ifndef __darkness_io_header__
#define __darkness_io_header__

#include"Types.h"

/// printf is not thread safe, so we need our own impletation
extern int darkPrintf(const char32_t* format, ...);

#endif //__darkness_io_header__
