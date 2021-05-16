#include"Debug.h"
#include"Utils.h"
#include"Vulkan.h"

/// Temporary headers
#include<stdio.h>
/// End of temporary headers

int dks_CreateVkInstance(struct dks_Info* dks, struct dks_Vulkan* vk)
{
   VkApplicationInfo app;
   VkInstanceCreateInfo info;

   if (0 == vk->version.major && 0 == vk->version.minor && 0 == vk->version.patch) {
      vk->version.major = 1;
      vk->version.minor = 2;
      vk->version.patch = 0;
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
   info.enabledExtensionCount = 0;
   info.ppEnabledExtensionNames = NULL;

   if (VK_SUCCESS != dks_LogCall(vkCreateInstance(&info, NULL, &vk->instance)))
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
   return 0;
}

int dks_CreateVkDevice(struct dks_Info* dks, struct dks_Vulkan* vk, struct dks_VkPhysicalDevices* dev)
{
   VkDeviceCreateInfo devInfo;
   return 0;
}

int dks_InitVulkan(struct dks_Info* dks)
{
   if (NULL == dks->vulkan)
      dks->vulkan = dks_MallocType(struct dks_Vulkan);

   if (0 != dks_LogCall(dks_CreateVkInstance(dks, dks->vulkan)))
      goto ERROR_EXIT;

   if (0 != dks_LogCall(dks_GetVkPhysicalDevices(dks, dks->vulkan, &dks->vulkan->physical)))
      goto ERROR_EXIT;
   
   if (0 != dks_LogCall(dks_SelectVkPhysicalDevice(dks, dks->vulkan, &dks->vulkan->physical)))
      goto ERROR_EXIT;

   return 0;
ERROR_EXIT:
   return -1;
}

