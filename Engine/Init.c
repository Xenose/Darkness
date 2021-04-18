#include<stdlib.h>
#include<stdio.h>
#include"Debug.h"
#include"Utils.h"
#include"Init.h"

void dark_CheckApplicationInfo(dark_Application* app)
{
   if (NULL == app->pName)
   {
      app->pName = dark_CreateString("default");
   }

   if (NULL == app->pEngineName)
   {
      app->pEngineName = dark_CreateString("Darkness");
   }

   if (0 >= app->windowSizeX || 0 >= app->windowSizeY)
   {
      app->windowSizeX = 1920;
      app->windowSizeY = 1080;
   }
}

int dark_InitDarkness(dark_Application* app, int arc, char** arv)
{
   
   if (!glfwInit())
   {
      puts("[ FAITAL ERROR ] :: failed to start glfw!");
      goto EXIT_0x01;
   }

   atexit(glfwTerminate);
   dark_CheckApplicationInfo(app);
  
   if (!glfwVulkanSupported())
   {
      app->flags |= DARKNESS_USE_OPENGL;
      puts("[ ERROR ] :: No vulkan support falling back to opengl");
   }
   else
   {
      dark_InitVulkan(app);
   }

   app->pWindow = glfwCreateWindow(app->windowSizeX, app->windowSizeY, app->pName, NULL, NULL);
   glfwMakeContextCurrent(app->pWindow);

   while(1)
   {
      glfwPollEvents();

      if (glfwWindowShouldClose(app->pWindow) || app->flags & DARKNESS_START_STOP)
      {
	 goto LOOP_EXIT;
      }
   }
LOOP_EXIT:

EXIT_0x01:
   return 0x0;
}
