#include"Debug.h"
#include"Utils.h"
#include"Vulkan.h"

/// Temporary headers
#include<stdio.h>
/// End of temporary headers

const char* requestedInstanceExtensions[] = {
};

char** dks_GetInstanceExtensions( uint32_t* count)
{
   uint32_t glfwCount = 0;
   const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwCount);

   *count = glfwCount + (sizeof(requestedInstanceExtensions) / 8);
   char** extensions = dks_MallocTypes(char*, *count);

   for (uint32_t i = 0; i < glfwCount; i++) {
      extensions[i] = dks_Crestr(glfwExtensions[i]);
   }

   if (glfwCount < *count) {
      for (uint32_t i = glfwCount; i < *count; i++) {
	 extensions[i] = dks_Crestr(requestedInstanceExtensions[i]);
      }
   }

   return extensions;
}

int dks_CreateVkInstance(struct dks_Info* dks, struct dks_Vulkan* vk)
{
   VkApplicationInfo app;
   VkInstanceCreateInfo info;
   uint32_t extensionCount = 0;
   uint32_t supportedAPI = 0;
   char** extensions = NULL;


   if (0 == vk->version.major && 0 == vk->version.minor && 0 == vk->version.patch) {
      vk->version.major = 1;
      vk->version.minor = 2;
      vk->version.patch = 0;
   }

   if (VK_SUCCESS != dks_LogCall(vkEnumerateInstanceVersion(&supportedAPI)))
      goto ERROR_EXIT;

   if (supportedAPI < VK_MAKE_VERSION(dks->engineVersion.major, dks->engineVersion.minor, dks->engineVersion.patch))
      goto ERROR_EXIT;

   if (NULL == (extensions = dks_GetInstanceExtensions(&extensionCount)))
      goto ERROR_EXIT;

   /* TO:DO Remove this later */
   for (uint32_t i = 0; i < extensionCount; i++) {
      printf("%s\n", extensions[i]);
   }

   app.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
   app.pNext = NULL;
   app.pApplicationName = dks->pName;
   app.pEngineName = dks->pEngineName;
   app.applicationVersion = VK_MAKE_VERSION(
	 dks->version.major, dks->version.minor, dks->version.patch);
   app.engineVersion = VK_MAKE_VERSION(
	 dks->engineVersion.major, dks->engineVersion.minor, dks->engineVersion.patch);
   app.apiVersion = VK_MAKE_VERSION(
	 vk->version.major, vk->version.minor, vk->version.patch);

   info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
   info.pNext = NULL;
   info.flags = 0x0;
   info.pApplicationInfo = &app;
   info.enabledLayerCount = 0;
   info.ppEnabledLayerNames = NULL;
   info.enabledExtensionCount = extensionCount;
   info.ppEnabledExtensionNames = (const char**)extensions;

   if (VK_SUCCESS != dks_LogCall(vkCreateInstance(&info, NULL, &vk->instance)))
      goto ERROR_EXIT;

   dks_Free(extensions);
   return 0;

ERROR_EXIT:
   if (NULL != extensions)
      dks_Free(extensions);
   return -1;
}

int dks_CreateVkSurface(struct dks_Info* dks, struct dks_Vulkan* vk)
{
   if (VK_SUCCESS != dks_LogCall(glfwCreateWindowSurface(vk->instance, dks->pWindow, NULL, &vk->surface)))
      goto ERROR_EXIT;

   return 0;
ERROR_EXIT:
   return -1;
}

const char* dks_GetVendorColour(uint32_t id)
{
   switch(id) {
      case 0x1002: // AMD
	 return "\033[31m";
      case 0x1010: // ImgTec
	 return "\033[35m";
      case 0x10DE: // NVidia
	 return "\033[32m";
      case 0x13B5: // ARM
	 return "\033[91m";
      case 0x5143: // Qualcomm
	 return "\033[94m";
      case 0x8086: // Intel
	 return "\033[34m";
   }

   return "";
}

int dks_GetVkPhysicalDevices(struct dks_Info* dks, struct dks_Vulkan* vk, struct dks_VkPhysicalDevices* dev)
{
   if (VK_SUCCESS != dks_LogCall(vkEnumeratePhysicalDevices(vk->instance, &dev->count, NULL)))
      goto ERROR_EXIT;

   dev->pDevices = dks_MallocTypes(VkPhysicalDevice, dev->count);
   dev->pProperties = dks_MallocTypes(VkPhysicalDeviceProperties, dev->count);
   dev->pFeatures = dks_MallocTypes(VkPhysicalDeviceFeatures, dev->count);

   if (NULL == dev->pDevices)
      goto ERROR_EXIT;
   
   if (VK_SUCCESS != dks_LogCall(vkEnumeratePhysicalDevices(vk->instance, &dev->count, dev->pDevices)))
	 goto ERROR_FREE_DEVICES;

   for (uint32_t i = 0; i < dev->count; i++) {
      vkGetPhysicalDeviceProperties(dev->pDevices[i], &dev->pProperties[i]);
      vkGetPhysicalDeviceFeatures(dev->pDevices[i], &dev->pFeatures[i]);

      printf("\n%s%u%s%s%s%s%s\n",
	    " [ PHYSICAL DEVICE :: ", i, " ]\n\n",
	    "\tDevice Name :\t", dks_GetVendorColour(dev->pProperties[i].vendorID), 
	    dev->pProperties[i].deviceName, "\033[0m\n");
   }

   return 0;
ERROR_FREE_DEVICES:
   dks_Free(dev->pDevices);
   dks_Free(dev->pProperties);
   dks_Free(dev->pFeatures);
   dev->count = 0;
ERROR_EXIT:
   return -1;
}

int dks_SelectVkPhysicalDevice(struct dks_Info* dks, struct dks_Vulkan* vk, struct dks_VkPhysicalDevices* dev)
{
   dev->index = 0;
   dev->pSelected = &dev->pDevices[dev->index];
   return 0;
}

uint32_t dks_VkFindQueueFamily(struct dks_VkPhysicalDevices* dev, const uint32_t flags)
{
   uint32_t count 			= 0;
   VkQueueFamilyProperties* properties	= NULL;

   vkGetPhysicalDeviceQueueFamilyProperties(*dev->pSelected, &count, NULL);
   properties = dks_MallocTypes(VkQueueFamilyProperties, count);
   vkGetPhysicalDeviceQueueFamilyProperties(*dev->pSelected, &count, properties);

   for (int i = 0; i < count; i++) {
      if (properties[i].queueFlags & flags) {
	 free(properties);
	 return i;
      }
   }

   return 0;
}

int dks_CreateVkDevice(struct dks_Info* dks, struct dks_Vulkan* vk, struct dks_VkPhysicalDevices* dev)
{
   VkDeviceCreateInfo		devInfo;
   VkDeviceQueueCreateInfo	queInfo;
   float			quePriorities = 1.0f;
   uint32_t			queIndex = vk->queueFamilyIndex = dks_VkFindQueueFamily(dev, VK_QUEUE_GRAPHICS_BIT);

   queInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
   queInfo.pNext = NULL;
   queInfo.flags = 0x0;
   queInfo.queueFamilyIndex = queIndex;
   queInfo.queueCount = 1;
   queInfo.pQueuePriorities = &quePriorities;

   devInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
   devInfo.pNext = NULL;
   devInfo.flags = 0x0;
   devInfo.pQueueCreateInfos = &queInfo;
   devInfo.queueCreateInfoCount = 1;
   devInfo.enabledLayerCount = 0;
   devInfo.enabledExtensionCount = 0;
   devInfo.ppEnabledLayerNames = NULL;
   devInfo.ppEnabledExtensionNames = NULL;
   devInfo.pEnabledFeatures = NULL;

   if (VK_SUCCESS != dks_LogCall(vkCreateDevice(*dev->pSelected, &devInfo, NULL, &vk->device)))
      goto ERROR_EXIT;

   vkGetDeviceQueue(vk->device, queIndex, 0, &vk->queue);

   return 0;
ERROR_EXIT:
   return -1;
}

int dks_CreateVkCommandPool(struct dks_Info* dks, struct dks_Vulkan* vk)
{
   VkCommandPoolCreateInfo info;

   info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
   info.pNext = NULL;
   info.flags = 0x0;
   info.queueFamilyIndex = vk->queueFamilyIndex;

   if (VK_SUCCESS != dks_LogCall(vkCreateCommandPool(vk->device, &info, NULL, &vk->pool)))
      goto ERROR_EXIT;

   return 0;
ERROR_EXIT:
   return -1;
}

int dks_InitVulkan(struct dks_Info* dks)
{
   if (NULL == dks->vulkan)
      dks->vulkan = dks_MallocType(struct dks_Vulkan);
   
   if (0 != dks_LogCall(dks_CreateVkInstance(dks, dks->vulkan)))
      goto ERROR_EXIT;
   
   if (0 != dks_LogCall(dks_CreateVkSurface(dks, dks->vulkan)))
      goto ERROR_EXIT;

   if (0 != dks_LogCall(dks_GetVkPhysicalDevices(dks, dks->vulkan, &dks->vulkan->physical)))
      goto ERROR_EXIT;
   
   if (0 != dks_LogCall(dks_SelectVkPhysicalDevice(dks, dks->vulkan, &dks->vulkan->physical)))
      goto ERROR_EXIT;

   if (0 != dks_LogCall(dks_CreateVkDevice(dks, dks->vulkan, &dks->vulkan->physical)))
      goto ERROR_EXIT;

   if (0 != dks_LogCall(dks_CreateVkCommandPool(dks, dks->vulkan)))
      goto ERROR_EXIT;

   return 0;
ERROR_EXIT:
   return -1;
}

