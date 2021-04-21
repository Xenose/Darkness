#include"Debug.h"
#include"Vulkan.h"

int dark_VkInitInstance(dark_Application* app, dark_Vulkan* vk)
{
   puts("[   LOG   ] Creating vulkan instance!");

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
   vkApp.apiVersion =			apiVersion;

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

int dark_VkPickPhysicalDevice(dark_Application* app, dark_Vulkan* vk)
{
   uint32_t deviceCount = 0;
   uint32_t selectedDeviceIndex = 0;
   VkPhysicalDevice* devices = NULL;
   VkPhysicalDeviceProperties properties;
   
   dark_VkCall(vkEnumeratePhysicalDevices(vk->instance, &deviceCount, NULL));

   devices = MallocTypes(VkPhysicalDevice, deviceCount);
   dark_VkCall(vkEnumeratePhysicalDevices(vk->instance, &deviceCount, devices));

   for (int i = 0; i < deviceCount; i++)
   {
      vkGetPhysicalDeviceProperties(devices[i], &properties);
   } 

   /// TODO :: Add a compilation flag to remove this on release versions 
   for (int i = 0; i < deviceCount; i++)
   {
      vkGetPhysicalDeviceProperties(devices[i], &properties);

      /// printing out the graphics info to stdout
      printf("\n%s%s%s%s%s%X%s%s%X%s%s%s%s%s%s%s\n",
	    "[ \033[35mDEVICE INFO\033[0m ] ", properties.deviceName, 
	    selectedDeviceIndex == i ? "\t[   \033[32mSelected\033[0m   ] " : "\t[ \033[31mNot Selected\033[0m ] ", 
	    "\n\n",
	    "\tVulkan API Version\t: 0x", properties.apiVersion, "\n",
	    "\tDriver Version\t\t: 0x", properties.driverVersion, "\n",
	    "\tManufacture\t\t: ", dark_VkGetNameFromVendorIDWithColor(properties.vendorID), "\n",
	    "\tDevice type\t\t: ", dark_VkGetDeviceTypeName(properties.deviceType), "\n");
   }

   vk->physicalDevice = devices[selectedDeviceIndex];
   free(devices);
   return 0x0;
}

VkQueueFamilyProperties dark_VkCreateQueue(dark_Application* app, dark_Vulkan* vk)
{
   uint32_t queueCount = 0;
   VkQueueFamilyProperties returnProperties;
   VkQueueFamilyProperties* queueProperties;

   vkGetPhysicalDeviceQueueFamilyProperties(vk->physicalDevice, &queueCount, NULL);
   queueProperties = MallocTypes(VkQueueFamilyProperties, queueCount);
   
   vkGetPhysicalDeviceQueueFamilyProperties(vk->physicalDevice, &queueCount, queueProperties);

   for (int i = 0; i < queueCount; i++)
   {
   }
   
   free(queueProperties);
   return returnProperties;
}

int dark_VkCreateDevice(dark_Application* app, dark_Vulkan* vk)
{
   return 0x0;
}

int dark_VkCreateSurface(dark_Application app, dark_Vulkan* vk)
{
   return 0x0;
}

int dark_InitVulkan(dark_Application* app)
{
   if (NULL == app->vulkan)
   {
      app->vulkan = MallocType(dark_Vulkan);
   }

   dark_VkInitInstance(app, app->vulkan);
   dark_VkPickPhysicalDevice(app, app->vulkan);

   return 0x0;
}
