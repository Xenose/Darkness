#ifndef __darkness_utils_header__
#define __darkness_utils_header__

#include<stdlib.h>
#include"Types.h"

#define dks_MallocType(type) (type*)malloc(sizeof(type))
#define dks_MallocTypes(type, count) (type*)malloc(sizeof(type) * (count))
#define dks_Free(ptr) free(ptr)

#define dks_Strlen(x) _Generic((x[0]),\
      char:	__dks_Strlen8((char*)x),\
      char16_t:	__dks_Strlen16((char16_t*)x),\
      char32_t: __dks_Strlen32((char32_t*)x))

#define dks_Strcpy(dst, src) _Generic((src[0]),\
      char:	__dks_Strcpy8((char*)dst,(char*)src),\
      char16_t:	__dks_Strcpy16((char16_t*)dst,(char16_t*)src),\
      char32_t: __dks_Strcpy32((char32_t*)dst,(char32_t*)src))


#define dks_Crestr(x) _Generic((x[0]),\
      char:	__dks_Crestr8((char*)x),\
      char16_t: __dks_Crestr16((char16_t*)x),\
      char32_t: __dks_Crestr32((char32_t*)x))

#define dks_ToString(x) _Generic((x),\
      int:		__dks_ToStringInt(x),\
      unsigned int:	__dks_ToStringUint(x),\
      float:		__dks_ToStringFloat(x),\
      double:		__dks_ToStringDouble(x))

extern size_t __dks_Strlen8(const char* text);
extern size_t __dks_Strlen16(const char16_t* text);
extern size_t __dks_Strlen32(const char32_t* text);

extern char* __dks_Strcpy8(char* dst, char* src);
extern char16_t* __dks_Strcpy16(char16_t* dst, char16_t* src);
extern char32_t* __dks_Strcpy32(char32_t* dst, char32_t* src);

extern char* 	 __dks_Crestr8(const char* text);
extern char16_t* __dks_Crestr16(const char16_t* text);
extern char32_t* __dks_Crestr32(const char32_t* text);

extern char* __dks_ToStringInt(int64_t i);
extern char* __dks_ToStringUint(uint64_t u);
extern char* __dks_ToStringFloat(float f);
extern char* __dks_ToStringDouble(double d);

#endif //__darkness_utils_header__
