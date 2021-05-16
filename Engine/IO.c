#include<unistd.h>
#include<stdio.h>
#include"IO.h"

int __dks_Puts8(const char* text)
{
   int out = write(1, text, dks_Strlen(text) * sizeof(char)) / sizeof(char) + 1;
   write(1, "\n", sizeof(char));
   return out;
}

int __dks_Puts16(const char16_t* text)
{
   int out = write(1, text, dks_Strlen(text) * sizeof(char16_t)) / sizeof(char16_t) + 1;
   write(1, u"\n", sizeof(char16_t));
   return out;
}

int __dks_Puts32(const char32_t* text)
{
   int out = write(1, text, dks_Strlen(text) * sizeof(char32_t)) / sizeof(char32_t);
   write(1, U"\n", sizeof(char32_t));
   return out;
}
