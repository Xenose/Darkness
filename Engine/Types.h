#ifndef __darkness_types_header__
#define __darkness_types_header__
#include<uchar.h>
#include<stdint.h>
#include<vulkan/vulkan.h>
#include<GL/glew.h>
#include<GLFW/glfw3.h>

#define int128_t __int128_t

#define DARKNESS_FLAG_USE_OPENGL	0x1
#define DARKNESS_FLAG_DRYRUN		0x2
#define DARKNESS_FLAG_GPU_OVERRIDE	0x4

#define DARKNESS_MODLE_TYPE_3D		0x1
#define DARKNESS_MODLE_TYPE_2D		0x2
#define DARKNESS_MODLE_TYPE_HALF	0x4

struct dks_Vector64x2 {
   int64_t x;
   int64_t y;
};

struct dks_Vector64x3 {
   int64_t x;
   int64_t y;
   int64_t z;
};

struct dks_Vector64x4 {
   int64_t x;
   int64_t y;
   int64_t z;
   int64_t a;
};

struct dks_Vector128x2 {
   int128_t x;
   int128_t y;
};

struct dks_Vector128x3 {
   int128_t x;
   int128_t y;
   int128_t z;
};

struct dks_Vector128x4 {
   int128_t x;
   int128_t y;
   int128_t z;
   int128_t a;
};

typedef struct __dks_Version {
   uint32_t major;
   uint32_t minor;
   uint32_t patch;
} dks_Version;

struct dks_Modle {
   struct dks_Vector128x3 position;
};

struct dks_Sprite {
};

struct dks_Scene {
   uint32_t id;
};

/* Here starts the engine specific types */

typedef struct __dks_VkInstance {

   uint32_t	extensionCount;
   char**	ppExtensions;

   VkApplicationInfo		aInfo;
   VkInstanceCreateInfo		cInfo;
   VkInstance			instance;
} dks_VkInstance;

typedef struct __dks_VkSurface {
   VkSurfaceKHR surface;
} dks_VkSurface;

typedef struct __dks_VkPhysicalDevices {
   uint32_t 			count;
   uint32_t			index;

   VkPhysicalDevice*		pSelected;

   VkPhysicalDevice*		pDevices;
   VkPhysicalDeviceProperties*	pProperties;
   VkPhysicalDeviceFeatures*	pFeatures;
} dks_VkPhysicalDevices;

typedef struct __dks_Vulkan {
   uint32_t	supportedAPI;
   dks_Version 	api;

   dks_VkInstance		instance;
   dks_VkSurface		surface;
   dks_VkPhysicalDevices	physical;

   uint32_t			queueFamilyIndex;
   VkDevice			device;
   VkQueue			queue;
   VkCommandPool		pool;
} dks_Vulkan;

struct dks_SystemInfo {
};

typedef struct __dks_Info {
   
   uint64_t flags;
   dks_Vulkan* vulkan;

   char* pName;
   char* pEngineName;
   dks_Version version;
   dks_Version engineVersion;

   GLFWwindow* pWindow;
   int windowSizeX;
   int windowSizeY;
} dks_Info;

#endif //__darkness_types_header__
