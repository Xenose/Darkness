#include<stdio.h>
#include<string.h>
#include"Debug.h"

// Gets the return codes name the func name and code
const char* ___dks_GetRetName(const char* fuName, intptr_t code)
{

   if (0 == strncmp("glfw", fuName, 4)) {
      
      switch(code){
	 case GLFW_TRUE:
	    return "\033[32mGLFW_TRUE\033[0m";
	 case GLFW_FALSE:
	    return "\033[31GLFW_FALSE\033[0m";
      } 
      goto END;
   }

   if (0 == strncmp("vk", fuName, 2)) {
      
      switch(code){
	 case VK_ERROR_FRAGMENTED_POOL:
	    return "VK_ERROR_FRAGMENTED_POOL";
	 case VK_ERROR_FORMAT_NOT_SUPPORTED:
	    return "VK_ERROR_FORMAT_NOT_SUPPORTED";
	 case VK_ERROR_TOO_MANY_OBJECTS:
	    return "VK_ERROR_TO_MANY_OBJECTS";
	 case VK_ERROR_INCOMPATIBLE_DRIVER:
	    return "VK_ERROR_INCOMPATIBLE_DRIVER";
	 case VK_ERROR_FEATURE_NOT_PRESENT:
	    return "VK_ERROR_FEATURE_NOT_PRESENT";
	 case VK_ERROR_EXTENSION_NOT_PRESENT:
	    return "VK_ERROR_EXTENSION_NOT_PRESENT";
	 case VK_ERROR_LAYER_NOT_PRESENT:
	    return "VK_ERROR_LAYER_NOT_PRESENT";
	 case VK_ERROR_MEMORY_MAP_FAILED:
	    return "VK_ERROR_MEMORY_MAP_FAILED";
	 case VK_ERROR_DEVICE_LOST:
	    return "VK_ERROR_DEVICE_LOST";
	 case VK_ERROR_INITIALIZATION_FAILED:
	    return "VK_ERROR_INITIALIIZATION_FAILED";
	 case VK_ERROR_OUT_OF_DEVICE_MEMORY:
	    return "VK_ERROR_OUT_OF_DEVICE_MEMORY";
	 case VK_ERROR_OUT_OF_HOST_MEMORY:
	    return "VK_ERROR_OUT_OF_HOST_MEMORY";
	 case VK_SUCCESS:
	    return "\033[32mVK_SUCCESS\033[0m";
	 case VK_NOT_READY:
	    return "VK_NOT_READY";
	 case VK_TIMEOUT:
	    return "VK_TIMEOUT";
	 case VK_EVENT_SET:
	    return "VK_EVENT_SET";
	 case VK_EVENT_RESET:
	    return "VK_EVENT_RESET";
	 case VK_INCOMPLETE:
	    return "VK_INCOMPLETE";
      } 
      goto END;
   }

   if (0 == strncmp("dks_", fuName, 4)) {
      
      switch(code){
	 case 0:
	    return "\033[32mDARKNESS NO ERROR\033[0m";
	 case -1:
	    return "\033[31DARKNESS ERROR\033[0m";
      } 
      goto END;
   }

   if (NULL == (void*)code)
   {
      return "NULL";
   }

END:
   return "Not found\n";
}


int ___dks_internal_log_call(intptr_t code, const char* fuName, const char* fiName, uint32_t line)
{
   fprintf(stderr, "\n%s\n\n%s%s\n%s%s\n%s%u\n%s%s\n\n",
	 " [ \033[32mFUNCTION LOG\033[0m ]",
	 "\tFunction Name ::\t", fuName,
	 "\tFile Name     ::\t", fiName,
	 "\tLine Number   ::\t", line,
	 "\tReturn Code   ::\t", ___dks_GetRetName(fuName, code));
   return code;
}
