#include<string.h>
#include"Utils.h"

uint32_t darkStrlen32(const char32_t* str)
{
   uint32_t count;
   for (count = 0; U'\0' != str[count]; count++);
   return count;
}

/// a simpe function for creating strings
char* dark_CreateString(const char* text)
{
   char* pTmp = MallocTypes(char, strlen(text));
   return  strcpy(pTmp, text);
}
