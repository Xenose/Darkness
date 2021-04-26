#include<unistd.h>
#include<time.h>
#include<stdio.h>
#include<stdarg.h>
#include"Types.h"
#include"Debug.h"


int (*dark_PrintLog)(const char* format, ...) = &__darkPrintLogNull;

/// The actual logging function
int __darkPrintLogOut(const char* format, ...)
{
   va_list args;
   va_start(args, format);

   write(1, "[   \033[93mLOG\033[0m   ] ", 22);
   printf(format, args);
   
   va_end(args);
   return 0x0;
}

/// A dummy function to void the logging output
int __darkPrintLogNull(const char* format, ...)
{
   return 0x0;
}

// This will translate VkResult codes into actual readble text
// for humans...
const char* __dark_GetVkReturnCode(int code)
{
   switch(code)
   {
      case VK_ERROR_FRAGMENTED_POOL:
	 return "VK_ERROR_FRAGMENTED_POOL";
      case VK_ERROR_FORMAT_NOT_SUPPORTED:
	 return "VK_ERROR_FORMAT_NOT_SUPPORTED";
      case VK_ERROR_TOO_MANY_OBJECTS:
	 return "VK_ERROR_TOO_MANY_OBJECTS";
      case VK_ERROR_INCOMPATIBLE_DRIVER:
	 return "VK_ERROR_INCOMPATIBLE_DRIVER";
      case VK_ERROR_FEATURE_NOT_PRESENT:
	 return "VK_ERROR_FEATURE_NOT_PRESENT";
      case VK_ERROR_EXTENSION_NOT_PRESENT:
	 return "VK_ERROR_EXTENSION_NO_PRESENT";
      case VK_ERROR_LAYER_NOT_PRESENT:
	 return "VK_ERROR_MEMORY_MAP_FAILED";
      case VK_ERROR_MEMORY_MAP_FAILED:
	 return "VK_ERROR_MEMORY_MAP_FAILED";
      case VK_ERROR_DEVICE_LOST:
	 return "VK_ERROR_DEVICE_LOST";
      case VK_ERROR_INITIALIZATION_FAILED:
	 return "VK_ERROR_INITIALIZATION_FAILED";
      case VK_ERROR_OUT_OF_DEVICE_MEMORY:
	 return "VK_ERROR_OUT_OF_DEVICE_MEMORY";
      case VK_ERROR_OUT_OF_HOST_MEMORY:
	 return "VK_ERROR_OUT_OF_HOST_MEMORY";
      case VK_SUCCESS:
	 return "VK_SUCCESS";
      case VK_NOT_READY:
	 return "VK_NOT_READY";
      case VK_TIMEOUT:
	 return "VK_TIMEOUT";
      case VK_EVENT_SET:
	 return "VK_EVENT_SET";
      case VK_INCOMPLETE:
	 return "VK_INCOMPLETE";
   }

   return "Unkown code";
}

int __darkVkCall(int code, const char* funcName, uint32_t line, const char* fileName)
{
   if (VK_SUCCESS != code)
   {
      printf("\n%s%d%s\n%s%s%c%s%s%c%s%u%c%s%s%c\n",
	    "[ \033[31mVULKAN ERROR\033[0m :: ", code, " ]\n",
	    "	Function ::	", funcName, '\n',
	    "	File Name ::	", fileName, '\n',
	    "	Line Number ::	", line, '\n',
	    "	Error Name ::	", __dark_GetVkReturnCode(code), '\n'
	 );

      return -0x1;
   }

   printf("[ \033[32mSUCCESS\033[0m ] %s\n", funcName);

   return 0x0;
}

// The benchmark time
struct timespec __oldTime;

void __dark_TimeBench()
{
  if (0 < __oldTime.tv_nsec)
  {
     struct timespec newTime;
     clock_gettime(CLOCK_REALTIME, &newTime);

     printf("[ TimeBench ] :: It took %ld nano second to run!\n", (newTime.tv_nsec - __oldTime.tv_nsec) / 100);
     __oldTime.tv_nsec = 0;
     return;
  }

  clock_gettime(CLOCK_REALTIME, &__oldTime);
}
