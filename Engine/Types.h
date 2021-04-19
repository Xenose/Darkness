#ifndef __darkness_types_header__
#define __darkness_types_header__

#include<stdint.h>
#include<vulkan/vulkan.h>
#include<GL/glew.h>
#include<GLFW/glfw3.h>

#define Main main // I like when functions uses the same style

#define DARKNESS_USE_OPENGL 0x01 // This flag forces darkness to use opengl instead of vulkan
#define DARKNESS_START_STOP 0x02 // This flag will start the program without being stuck in loop
#define DARKNESS_DEBUG_MODE 0x04 // This flag will add additional debug functions to the code

typedef struct __dark_Vulkan {
   VkInstance instance;
} dark_Vulkan;

typedef struct __dark_Application {
  
   uint32_t flags;
   dark_Vulkan* vulkan;

   char*	pName;
   const char*	pEngineName;
   GLFWwindow*	pWindow;

   uint32_t windowSizeX;
   uint32_t windowSizeY;
} dark_Application;

#endif //__darknes_types_header__
