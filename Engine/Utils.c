#include<math.h>
#include"Utils.h"

// tmp headers
#include<unistd.h>
#include<stdio.h>
// tmp headers end

size_t __dks_Strlen8(const char* text)
{
   size_t i = 0;
   while('\0' != text[i++]) {}
   return i + 1;
}

size_t __dks_Strlen16(const char16_t* text)
{
   size_t i = 0;
   while(u'\0' != text[i++]) {}
   return i + 1;
}

size_t __dks_Strlen32(const char32_t* text)
{
   size_t i = 0;
   while(U'\0' != text[i++]) {}
   return i + 1;
}

/// The strcpy functions

char* __dks_Strcpy8(char* dst, char* src)
{
   uint32_t i;
   for (i = 0; '\0' != src[i]; i++) {
      dst[i] = src[i];
   }
   
   dst[i] = '\0';
   return dst;
}

char16_t* __dks_Strcpy16(char16_t* dst, char16_t* src)
{
   uint32_t i;
   for (i = 0; u'\0' != src[i]; i++) {
      dst[i] = src[i];
   }

   dst[i] = u'\0';
   return dst;
}

char32_t* __dks_Strcpy32(char32_t* dst, char32_t* src)
{
   uint32_t i;
   for (i = 0; U'\0' != src[i]; i++) {
      dst[i] = src[i];
   }

   dst[i] = U'\0';
   return dst;
}

/// The Crestr functions starts here

char* __dks_Crestr8(const char* text)
{
   char* tmp = dks_MallocTypes(char, dks_Strlen(text));
   dks_Strcpy(tmp, text);
   return tmp;
}

char16_t* __dks_Crestr16(const char16_t* text)
{
   char16_t* tmp = dks_MallocTypes(char16_t, dks_Strlen(text));
   dks_Strcpy(tmp, text);
   return tmp;
}
char32_t* __dks_Crestr32(const char32_t* text)
{ 
   char32_t* tmp = dks_MallocTypes(char32_t, dks_Strlen(text));
   dks_Strcpy(tmp, text);
   return tmp;
}

/// The ToString functions starts here

char* __dks_ToStringInt(int64_t x)
{ 
   char* tmp;
   uint32_t length = 1;
   char c = 0;

   if (0 > x) {
      length++;
      c = '-';
   }

   x = labs(x);

   if (10 < labs(x)){
      length += log10(x);
   }

   tmp = dks_MallocTypes(char, length);

   if (0 != c)
      tmp[0] = c;
   
   for (uint32_t i = length - 1, y = x; 0 < y; y *= 0.1f, i--) {
      int z = y % 10;
      tmp[i] = z + '0';
   }

   return tmp;
}

char* __dks_ToStringUint(uint64_t x)
{
   char* tmp;
   uint32_t length = 1;

   if (10 < x){
      length += log10(x);
   }

   tmp = dks_MallocTypes(char, length);
   
   for (uint32_t i = length - 1, y = x; 0 < y; y *= 0.1f, i--) {
      int z = y % 10;
      tmp[i] = z + '0';
   }

   return tmp;
}

char* __dks_ToStringFloat(float x)
{
   int e = (int)x;
   float y = x - e;
   char* tmp = __dks_ToStringInt(e);

   uint32_t m = 0;

   printf("\n%u\n", m);

   return tmp;
}

char* __dks_ToStringDuoble(double x)
{
   return NULL;
}

