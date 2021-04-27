#include<unistd.h>
#include<string.h>
#include<math.h>
#include"IO.h"

int darkGetFormatadedStringLength(const char32_t* format)
{
   return 0;
}

/// implementing a thread safe printf
int darkPrintf(const char32_t* format, ...)
{
   va_list args, argsCopy;
   int fsl;// = strlen(format); /// The formated string length
   int osl = 0; /// The output string lenght

   va_start(args, format);
   va_copy(argsCopy, args);

   for (int i = 0; i < fsl; i++)
   {
      if(U'%' == format[i])
      {
	 switch(format[++i])
	 {
	    case U'd':
	    case U'i':
	       osl += log10(va_arg(args, int));
	       break;
	    case U'u':
	       osl += log10(va_arg(args, unsigned int));
	       break;
	    case U'o':
	       break;
	    case U'x':
	       break;
	    case U'X':
	       break;
	    case U'F':
	    case U'f':
	       osl += log10(va_arg(args, double)) + 7;
	       break;
	    case U'e':
	       break;
	    case U'E':
	       break;
	    case U'g':
	       break;
	    case U'G':
	       break;
	    case U'a':
	       break;
	    case U'A':
	       break;
	    case U'c':
	       osl++;
	       break;
	    case U's':
	       break;
	    case U'p':
	       break;
	    case U'n':
	       break;
	    case U'%':
	       osl++;
	       break;
	 }
      }
   }

   return 0x0;
}
