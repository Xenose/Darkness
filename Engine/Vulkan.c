#include"Debug.h"
#include"Utils.h"
#include"Vulkan.h"

/// Temporary headers
#include<stdio.h>
/// End of temporary headers

const char* requestedInstanceExtensions[] = {
};

char** dks_GetInstanceExtensions(uint32_t* count)
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

int dks_CreateVkInstance(dks_Info* dks, dks_Vulkan* vk, dks_VkInstance* inst)
{
   if (0 == vk->api.major && 0 == vk->api.minor && 0 == vk->api.patch) {
      vk->api.major = 1;
      vk->api.minor = 2;
      vk->api.patch = 0;
   }

   if (VK_SUCCESS != dks_LogCall(vkEnumerateInstanceVersion(&vk->supportedAPI)))
      goto ERROR_EXIT;

   if (vk->supportedAPI > VK_MAKE_VERSION(vk->api.major, vk->api.minor, vk->api.patch))
      goto ERROR_EXIT;

   if (NULL == (inst->ppExtensions = dks_GetInstanceExtensions(&inst->extensionCount)))
      goto ERROR_EXIT;

   inst->aInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
   inst->aInfo.pNext = NULL;
   inst->aInfo.pApplicationName = dks->pName;
   inst->aInfo.pEngineName = dks->pEngineName;
   inst->aInfo.applicationVersion = VK_MAKE_VERSION(
	 dks->version.major, dks->version.minor, dks->version.patch);
   inst->aInfo.engineVersion = VK_MAKE_VERSION(
	 dks->engineVersion.major, dks->engineVersion.minor, dks->engineVersion.patch);
   inst->aInfo.apiVersion = VK_MAKE_VERSION(
	 vk->api.major, vk->api.minor, vk->api.patch);

   inst->cInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
   inst->cInfo.pNext = NULL;
   inst->cInfo.flags = 0x0;
   inst->cInfo.pApplicationInfo = &inst->aInfo;
   inst->cInfo.enabledLayerCount = 0;
   inst->cInfo.ppEnabledLayerNames = NULL;
   inst->cInfo.enabledExtensionCount = inst->extensionCount;
   inst->cInfo.ppEnabledExtensionNames = (const char**)inst->ppExtensions;

   if (VK_SUCCESS != dks_LogCall(vkCreateInstance(&inst->cInfo, NULL, &inst->instance)))
      goto ERROR_EXIT;

   return 0;
ERROR_EXIT:
   return -1;
}

int dks_CreateVkSurface(dks_Info* dks, dks_VkInstance* inst, dks_VkSurface* sur)
{
   if (VK_SUCCESS != dks_LogCall(glfwCreateWindowSurface(inst->instance, dks->pWindow, NULL, &sur->surface)))
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

int dks_GetVkPhysicalDevices(dks_VkInstance* inst, dks_VkPhysicalDevices* dev)
{
   if (VK_SUCCESS != dks_LogCall(vkEnumeratePhysicalDevices(inst->instance, &dev->count, NULL)))
      goto ERROR_EXIT;

   dev->pDevices = dks_MallocTypes(VkPhysicalDevice, dev->count);
   dev->pProperties = dks_MallocTypes(VkPhysicalDeviceProperties, dev->count);
   dev->pFeatures = dks_MallocTypes(VkPhysicalDeviceFeatures, dev->count);

   if (NULL == dev->pDevices)
      goto ERROR_EXIT;
   
   if (VK_SUCCESS != dks_LogCall(vkEnumeratePhysicalDevices(inst->instance, &dev->count, dev->pDevices)))
	 goto ERROR_EXIT;

   for (uint32_t i = 0; i < dev->count; i++) {
      vkGetPhysicalDeviceProperties(dev->pDevices[i], &dev->pProperties[i]);
      vkGetPhysicalDeviceFeatures(dev->pDevices[i], &dev->pFeatures[i]);

      printf("\n%s%u%s%s%s%s%s\n",
	    " [ PHYSICAL DEVICE :: ", i, " ]\n\n",
	    "\tDevice Name :\t", dks_GetVendorColour(dev->pProperties[i].vendorID), 
	    dev->pProperties[i].deviceName, "\033[0m\n");
   }

   return 0;
ERROR_EXIT:
   return -1;
}



int dks_SelectVkPhysicalDevice(dks_Info* dks, dks_Vulkan* vk, dks_VkPhysicalDevices* dev)
{
   dev->index = 0;
   dev->pSelected = &dev->pDevices[dev->index];
   return 0;
}



uint32_t dks_VkFindQueueFamily(dks_VkPhysicalDevices* dev, const uint32_t flags)
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



int dks_CreateVkDevice(dks_Info* dks, dks_Vulkan* vk, dks_VkPhysicalDevices* dev)
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



int dks_CreateVkCommandPool(dks_Info* dks, dks_Vulkan* vk)
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



int dks_InitVulkan(dks_Info* dks)
{
   if (NULL == dks->vulkan)
      dks->vulkan = dks_MallocType(dks_Vulkan);

   dks_Vulkan* vk = dks->vulkan;
   

   if (0 != dks_LogCall(dks_CreateVkInstance(dks, vk, &vk->instance)))
      goto ERROR_EXIT;
   
   if (0 != dks_LogCall(dks_CreateVkSurface(dks, &vk->instance, &vk->surface)))
      goto ERROR_EXIT;

   if (0 != dks_LogCall(dks_GetVkPhysicalDevices(&vk->instance, &vk->physical)))
      goto ERROR_EXIT;
   
   if (0 != dks_LogCall(dks_SelectVkPhysicalDevice(dks, vk, &vk->physical)))
      goto ERROR_EXIT;

   if (0 != dks_LogCall(dks_CreateVkDevice(dks, vk, &vk->physical)))
      goto ERROR_EXIT;

   if (0 != dks_LogCall(dks_CreateVkCommandPool(dks, vk)))
      goto ERROR_EXIT;

   return 0;
ERROR_EXIT:
   return -1;
}

