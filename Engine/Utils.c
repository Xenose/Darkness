#include<string.h>
#include"Utils.h"

/// a simpe function for creating strings
char* dark_CreateString(const char* text)
{
   char* pTmp = MallocTypes(char, strlen(text));
   return  strcpy(pTmp, text);
}
