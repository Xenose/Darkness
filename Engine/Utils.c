#include<string.h>
#include"Utils.h"

char* dark_CreateString(const char* text)
{
   char* pTmp = MallocTypes(char, strlen(text));
   return  strcpy(pTmp, text);
}
