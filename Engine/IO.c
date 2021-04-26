#include<unistd.h>
#include<string.h>
#include<math.h>
#include"IO.h"


int darkPrintf(const uchar* format, ...)
{
   va_list args, argsCopy;
   int fsl = strlen(format); /// The formated string length
   int osl = 0; /// The output string lenght

   va_start(args, format);
   va_copy(argsCopy, args);

   for (int i = 0; i < fsl; i++)
   {
      if('%' == format[i])
      {
	 switch(format[++i])
	 {
	    case 'd':
	    case 'i':
	       osl += log10(va_arg(args, int));
	       break;
	    case 'u':
	       osl += log10(va_arg(args, unsigned int));
	       break;
	    case 'o':
	       break;
	    case 'x':
	       break;
	    case 'X':
	       break;
	    case 'f':
	       break;
	    case 'F':
	       break;
	    case 'e':
	       break;
	    case 'E':
	       break;
	    case 'g':
	       break;
	    case 'G':
	       break;
	    case 'a':
	       break;
	    case 'A':
	       break;
	    case 'c':
	       osl++;
	       break;
	    case 's':
	       break;
	    case 'p':
	       break;
	    case 'n':
	       break;
	    case '%':
	       osl++;
	       break;
	 }
      }
   }

   return 0x0;
}
