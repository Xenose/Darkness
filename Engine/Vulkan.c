#include"Debug.h"
#include"Vulkan.h"

int dark_VkInitInstance(dark_Application* app, dark_Vulkan* vulkan)
{
   puts("[ LOG ] :: Creating vulkan instance!");
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

   dark_VkCall(vkCreateInstance(&vkInfo, NULL, &vulkan->instance));

   return 0x0;
}

int dark_VkPickDevice(dark_Application* app, dark_Vulkan* vulkan)
{
   return 0x0;
}

int dark_VkCreateDevice(dark_Application* app, dark_Vulkan* vulkan)
{
   return 0x0;
}

int dark_VkCreateSurface(dark_Application app, dark_Vulkan* vulkan)
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

   return 0x0;
}
