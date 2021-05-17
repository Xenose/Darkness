#include<stdio.h>
#include<string.h>
#include"Debug.h"

/* Gets the return codes name the func name and code */
const char* ___dks_GetRetName(const char* fuName, int64_t code, int* logLevel)
{
   /* Some functions are special cases and need to be check before the others */
   if (0 == strncmp(fuName, "glfwCreateWindowSurface", 23))
      goto VULKAN;

   if (0 == strncmp("glfw", fuName, 4)) {
GLFW: /* A label for special cases */ 
      switch(code){
	 case GLFW_TRUE:
	    return "\033[32mGLFW_TRUE\033[0m";
	 case GLFW_FALSE:
	    *logLevel = 1;
	    return "\033[31mGLFW_FALSE\033[0m";
	 case GLFW_NOT_INITIALIZED:
	    *logLevel = 1;
	    return "\033[31mGLFW_NOT_INITIALIZED\033[0m";
      } 
      goto END;
   }

   if (0 == strncmp("vk", fuName, 2)) {
VULKAN: /* A label for special cases */
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
	    return "\033[31mVK_ERROR_EXTENSION_NOT_PRESENT\033[0m";
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
	    return "\033[31mDARKNESS ERROR\033[0m";
      } 
      goto END;
   }

END:
   return "Not found\n";
}


int ___dks_internal_log_call(int64_t code, const char* fuName, const char* fiName, uint32_t line)
{
   int logLevel = 0;
   const char* codeName = ___dks_GetRetName(fuName, code, &logLevel);

   switch (logLevel)
   {
      default:
	 fprintf(stderr, "%s\n\n%s%s\n%s%s\n%s%u\n%s%lu\n%s%s\n\n",
	       " [ \033[31m ERROR \033[0m ]",
	       "\tFunction Name ::\t", fuName,
	       "\tFile Name     ::\t", fiName,
	       "\tLine Number   ::\t", line,
	       "\tReturn Code   ::\t", code,
	       "\tError Name    ::\t", codeName);
	 break;
      case 0:
	 fprintf(stderr, " [ \033[32mSUCCESS\033[0m ] ::\t %s ( %s )\n", fuName, codeName);
	 break;
   }
   return code;
}
