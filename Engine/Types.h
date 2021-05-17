#ifndef __darkness_types_header__
#define __darkness_types_header__
#include<uchar.h>
#include<stdint.h>
#include<vulkan/vulkan.h>
#include<GL/glew.h>
#include<GLFW/glfw3.h>

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
   __int128_t x;
   __int128_t y;
};

struct dks_Vector128x3 {
   __int128_t x;
   __int128_t y;
   __int128_t z;
};

struct dks_Vector128x4 {
   __int128_t x;
   __int128_t y;
   __int128_t z;
   __int128_t a;
};

struct dks_Version {
   uint32_t major;
   uint32_t minor;
   uint32_t patch;
};

struct dks_Modle {
   struct dks_Vector128x3 position;
};

struct dks_Sprite {
};

struct dks_Scene {
   uint32_t id;
};

struct dks_VkPhysicalDevices {
   uint32_t 			count;
   uint32_t			index;
   
   VkPhysicalDevice*		pSelected;

   VkPhysicalDevice*		pDevices;
   VkPhysicalDeviceProperties*	pProperties;
   VkPhysicalDeviceFeatures*	pFeatures;
};

struct dks_Vulkan {
   struct dks_Version version;
   
   VkInstance			instance;
   VkSurfaceKHR 		surface;
   struct dks_VkPhysicalDevices physical;

   uint32_t			queueFamilyIndex;
   VkDevice			device;
   VkQueue			queue;
   VkCommandPool		pool;
};

struct dks_SystemInfo {
};

struct dks_Info {
   
   uint64_t flags;
   struct dks_Vulkan* vulkan;

   char* pName;
   char* pEngineName;
   struct dks_Version version;
   struct dks_Version engineVersion;

   GLFWwindow* pWindow;
   int windowSizeX;
   int windowSizeY;
};

#endif //__darkness_types_header__
