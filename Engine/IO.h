#ifndef __darkness_io_header__
#define __darkness_io_header__

#include"Types.h"
#include"Utils.h"

#define dks_Puts(x) _Generic((x[0]),\
	 char:		__dks_Puts8((char*)x),\
	 char16_t:	__dks_Puts16((char16_t*)x),\
	 char32_t:	__dks_Puts32((char32_t*)x))

extern int __dks_Puts8(const char* text);
extern int __dks_Puts16(const char16_t* text);
extern int __dks_Puts32(const char32_t* text);

#endif //__darkness_io_header__
