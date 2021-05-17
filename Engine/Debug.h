#ifndef __darkness_debug_header__
#define __darkness_debug_header__

#define DARKNESS_DEBUG_COMPILE

#include"Types.h"

#ifdef DARKNESS_DEBUG_COMPILE
   #define dks_LogCall(func) ___dks_internal_log_call(func, #func, __FILE__, __LINE__)
#else
   #define dks_LogCall(func) func
#endif

extern int ___dks_internal_log_call(int64_t code, const char* fuName, const char* fiName, uint32_t line);

#endif //__darkness_debug_header__
