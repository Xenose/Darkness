#ifndef __darkness_utils_header__
#define __darkness_utils_header__

#include<stdlib.h>

#define MallocType(type) (type*) malloc(sizeof(type));
#define MallocTypes(type, count) (type*) malloc(sizeof(type) * (count))

extern char* dark_CreateString(const char* text);

#endif //__darkness_utils_header__
