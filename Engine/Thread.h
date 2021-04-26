#ifndef __darkness_thread_header__
#define __darkness_thread_header__
#include<setjmp.h>

#define TRY
#define CATCH else
#define ASSERT(code) longjmp( code) 

#endif //__darkness_thread_header__
