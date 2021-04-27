#ifndef __darkness_utils_header__
#define __darkness_utils_header__

#include"Types.h"
#include"Memory.h"

#define MallocType(type) (type*) darkMalloc(sizeof(type));
#define MallocTypes(type, count) (type*) darkMalloc(sizeof(type) * (count))

extern uint32_t darkStrlen32(const char32_t* str);
extern char* dark_CreateString(const char* text);

#endif //__darkness_utils_header__
