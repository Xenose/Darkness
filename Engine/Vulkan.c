#include"Debug.h"
#include"Vulkan.h"

int darkVkInitInstance(darkApplication* app, darkVulkan* vk)
{
   dark_PrintLog("Creating vulkan instance!\n");

   uint32_t apiVersion = 0;
   dark_VkCall(vkEnumerateInstanceVersion(&apiVersion));

   if (VK_MAKE_VERSION(1,2,0) > apiVersion)
   {
      return -0x1;
   }

   VkApplicationInfo vkApp;
   VkInstanceCreateInfo vkInfo;

   vkApp.sType =			VK_STRUCTURE_TYPE_APPLICATION_INFO;
   vkApp.pNext =			NULL;
   vkApp.pApplicationName =		app->pName;
   vkApp.pEngineName =			app->pEngineName;
   vkApp.applicationVersion =		VK_MAKE_VERSION(0,0,1);
   vkApp.engineVersion =		VK_MAKE_VERSION(0,0,1);
   vkApp.apiVersion =			VK_MAKE_VERSION(1,2,0);

   vkInfo.sType =			VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
   vkInfo.pNext =			NULL;
   vkInfo.flags =			0x0;
   vkInfo.pApplicationInfo =		&vkApp;
   vkInfo.ppEnabledExtensionNames =	NULL;
   vkInfo.enabledExtensionCount = 	0;
   vkInfo.ppEnabledLayerNames =		NULL;
   vkInfo.enabledLayerCount = 		0;

   dark_VkCall(vkCreateInstance(&vkInfo, NULL, &vk->instance));

   return 0x0;
}

/// Getting the company name for logging and other uses cases maybe?
const char* dark_VkGetNameFromVendorIDWithColor(uint32_t id)
{
   switch(id)
   {
      case 0x1002:
	return "\033[31mAMD\033[0m";
      case 0x1010:
	return "\033[31mImgTec\033[0m";
      case 0x10DE:
	return "\033[32mNVIDIA\033[0m"; 
      case 0x13B5:
	return "\033[31mARM\033[0m";
      case 0x5143:
	return "\033[31mQualcomm\033[0m";
      case 0x8086:
	return "\033[36mIntel\033[0m";
   }

   return "Unkowned";
}

/// A function for getting a human readble name on the type of graphics used.
const char* dark_VkGetDeviceTypeName(VkPhysicalDeviceType type)
{
   switch ((uint32_t)type)
   {
      case 0:
	 return "OTHER";
      case 1:
	 return "ITEGRATED";
      case 2:
	 return "DISCRETE";
      case 3:
	 return "VIRTUAL";
      case 4:
	 return "CPU";
   }

   return "unkowned";
}

int dark_VkPickPhysicalDevice(darkApplication* app, darkVulkan* vk)
{
   dark_PrintLog("Picking physical device!\n");
   
   uint32_t deviceCount = 0;
   uint32_t selectedDeviceIndex = 0;

   VkPhysicalDevice* devices = NULL;
   VkPhysicalDeviceProperties* properties = NULL;
   
   dark_VkCall(vkEnumeratePhysicalDevices(vk->instance, &deviceCount, NULL));

   devices = MallocTypes(VkPhysicalDevice, deviceCount);
   properties = MallocTypes(VkPhysicalDeviceProperties, deviceCount);

   dark_VkCall(vkEnumeratePhysicalDevices(vk->instance, &deviceCount, devices));

   for (int i = 0; i < deviceCount; i++)
   {
      vkGetPhysicalDeviceProperties(devices[i], &properties[i]);
   } 

   /// TODO :: Add a compilation flag to remove this on release versions 
   for (int i = 0; i < deviceCount; i++)
   {
      /// I want something cleaner...
      /// printing out the graphics info to stdout
      printf("\n%s%s%s%s%s%X%s%s%X%s%s%s%s%s%s%s\n",
	    "[ \033[35mDEVICE INFO\033[0m ] ", properties[i].deviceName, 
	    selectedDeviceIndex == i ? "\t\t[   \033[32mSelected\033[0m   ] " : "\t\t[ \033[31mNot Selected\033[0m ] ", 
	    "\n\n",
	    "\tVulkan API Version\t: 0x", properties[i].apiVersion, "\n",
	    "\tDriver Version\t\t: 0x", properties[i].driverVersion, "\n",
	    "\tManufacture\t\t: ", dark_VkGetNameFromVendorIDWithColor(properties[i].vendorID), "\n",
	    "\tDevice type\t\t: ", dark_VkGetDeviceTypeName(properties[i].deviceType), "\n");
   }

   vk->physicalDevice = devices[selectedDeviceIndex];
   darkFree(devices);
   darkFree(properties);
   return 0x0;
}

int dark_VkGetQueueInfo(darkApplication* app, darkVulkan* vk, 
      VkQueueFamilyProperties* returnProperties, const VkQueueFlags flags)
{
   dark_PrintLog("Getting queue infos!\n");
   
   int index = 0;
   uint32_t queueCount = 0;
   VkQueueFamilyProperties* queueProperties;

   vkGetPhysicalDeviceQueueFamilyProperties(vk->physicalDevice, &queueCount, NULL);
   queueProperties = MallocTypes(VkQueueFamilyProperties, queueCount);
   
   vkGetPhysicalDeviceQueueFamilyProperties(vk->physicalDevice, &queueCount, queueProperties);

   for (int i = 0; i < queueCount; i++)
   {
      if (flags & queueProperties[i].queueFlags)
      {
	 *returnProperties = queueProperties[i];
	 index = i;
	 break;
      }
   }
   
   darkFree(queueProperties);
   return index;
}

int dark_VkCreateDevice(darkApplication* app, darkVulkan* vk)
{
   VkDeviceCreateInfo vkInfo;
   VkDeviceQueueCreateInfo vkQueue;
   VkQueueFamilyProperties queueProperties;

   float queuePriority = 1;
   int queueFamilyIndex = dark_VkGetQueueInfo(app, vk, &queueProperties, VK_QUEUE_GRAPHICS_BIT);

   vkQueue.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
   vkQueue.pNext = NULL;
   vkQueue.flags = 0x0;
   vkQueue.queueFamilyIndex = queueFamilyIndex;
   vkQueue.queueCount = 1;
   vkQueue.pQueuePriorities = &queuePriority;

   vkInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
   vkInfo.pNext = NULL;
   vkInfo.flags = 0x0;
   vkInfo.enabledLayerCount = 0;
   vkInfo.ppEnabledLayerNames = NULL;
   vkInfo.enabledExtensionCount = 0;
   vkInfo.ppEnabledExtensionNames = NULL;
   vkInfo.pQueueCreateInfos = &vkQueue;
   vkInfo.queueCreateInfoCount = 1;
   vkInfo.pEnabledFeatures = NULL;

   dark_VkCall(vkCreateDevice(vk->physicalDevice, &vkInfo, NULL, &vk->graphicsDevice));
   vkGetDeviceQueue(vk->graphicsDevice, queueFamilyIndex, 0, &vk->graphicsQueue);
   return 0x0;
}

int dark_VkCreateSurface(darkApplication app, darkVulkan* vk)
{
   return 0x0;
}

int dark_InitVulkan(darkApplication* app)
{
   dark_PrintLog("Initializing Vulkan!\n");

   if (NULL == app->vulkan)
   {
      app->vulkan = MallocType(darkVulkan);
   }

   darkVkInitInstance(app, app->vulkan);
   dark_VkPickPhysicalDevice(app, app->vulkan);
   dark_VkCreateDevice(app, app->vulkan);

   return 0x0;
}
