#ifndef __darkness_debug_header__
#define __darkness_debug_header__

#include<stdint.h>
#include<stdio.h>

#define dark_VkCall(func) __dark_VkCall(func, #func, __LINE__, __FILE__)
#define dark_TimeBench(func) __dark_TimeBench(); func; __dark_TimeBench()

extern int __dark_VkCall(int code, const char* funcName, uint32_t line, const char* fileName);
extern void __dark_TimeBench();

#endif //__darkness_debug_header__
