#ifndef __darkness_types_header__
#define __darkness_types_header__

#define __STD_UTF_16__
#define __STD_UTF_32__

#include<uchar.h>
#include<stdint.h>
#include<vulkan/vulkan.h>
#include<GL/glew.h>
#include<GLFW/glfw3.h>

#define Main main // I like when functions uses the same style

#define DARKNESS_USE_OPENGL 	0x01 // This flag forces darkness to use opengl instead of vulkan
#define DARKNESS_START_STOP 	0x02 // This flag will start the program without being stuck in loop
#define DARKNESS_DEBUG_MODE 	0x04 // This flag will add additional debug functions to the code
#define DARKNESS_NO_GRAPHICS	0x08 // Use the engine without any graphics

#define DARKNESS_COLOR_RGB	0x01
#define DARKNESS_COLOR_CMY	0x02

typedef struct __darkVertex2F {
   float x, y;
} darkVertex2F;

typedef struct __darkVertex3F {
   float x, y, z;
} darkVertex3F;

typedef struct __darkVertex4F {
   float x, y, z, a;
} darkVertex4F;

typedef struct __darkColor {
   
   unsigned char color_type;

   union {
      unsigned char r;
      unsigned char c;
      unsigned char h;
   };

   union {
      unsigned char g;
      unsigned char m;
      unsigned char s;
   };

   union {
      unsigned char b;
      unsigned char y;
      unsigned char l;
   };

   union {
      unsigned char a;
      unsigned char k;
   };

} darkColor;

typedef struct __darkVulkan {
   VkInstance		instance;
   VkPhysicalDevice	physicalDevice;
   VkDevice		graphicsDevice;
   VkQueue		graphicsQueue;
   VkSurfaceKHR		surface;
   VkCommandPool	commandPool;
} darkVulkan;

// Information about the system useful to the engine
typedef struct __darkSystemInfo {
   unsigned short	cpuCoreCount; // The total number of cores in the system
   unsigned short	cpuThreadCount;	// The total amount of thread in the system
   unsigned int		maxMemory; // The total amount of memory in the system
} darkSystemInfo;

// The main information for the application/game
typedef struct __darkApplication {
  
   uint32_t flags;
   darkVulkan* vulkan;

   char*	pName;
   char*	pEngineName;
   GLFWwindow*	pWindow;

   int windowSizeX;
   int windowSizeY;

   void (*EngineLoop)(void);
} darkApplication;

#endif //__darknes_types_header__
