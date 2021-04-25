#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include"Debug.h"
#include"Utils.h"
#include"Init.h"

/// This is just the help info that gets printed when typing help
void dark_PrintHelpInfo()
{
   printf("%s%s%s%s",
	 "\n\nThese are the debug/launch commands for the darkness engine:\n\n",
	 "\thelp\t:: will list this help page\n\n",
	 "\tdrun\t:: will exit the program without waithing for user input\n", /// debug run
	 "\topengl\t:: will launch the engine in opengl mode\n");
}

void dark_ParseInputArgs(dark_Application* app, int arc, char** arv)
{
   if (arc > 1)
   {
      for (int i = 1; i < arc; i++)
      {
	 // sorting the commands by first char to reduce if statments
	 switch(arv[i][0])
	 {
	    default:
	    case 'd':
	       if (!strcmp(arv[i], "debug"))
	       {
		  dark_PrintLog = &__dark_PrintLogOut;
		  dark_PrintLog("Entering debug mode!\n");
		  break;
	       }
	       if (!strcmp(arv[i], "drun"))
	       {
		  app->flags |= DARKNESS_START_STOP;
		  break;
	       }
	    case 'h':
	       if (!strcmp(arv[i], "help"))
	       {
		  dark_PrintHelpInfo();
		  exit(0);
	       }
	    case 'o':
	       if (!strcmp(arv[i], "opengl"))
	       {
		  app->flags |= DARKNESS_USE_OPENGL;
		  puts("Selected OpenGL mode for rendering");
		  break;
	       }
	 }
      }
   }
}

/// This function is for checking all the basic information and
/// fixing any basic errors
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
   dark_ParseInputArgs(app, arc, arv);

   if (!glfwInit())
   {
      puts("[ FAITAL ERROR ] :: failed to start glfw!");
      goto EXIT_ERROR_0x01;
   }

   dark_CheckApplicationInfo(app);
 
   /// if vulkan isn't supported then opengl will take over 
   if (!glfwVulkanSupported())
   {
      app->flags |= DARKNESS_USE_OPENGL;
      puts("[ ERROR ] :: No vulkan support falling back to opengl");
   }
   else if (!(app->flags & DARKNESS_USE_OPENGL))
   {
      /// the vulkan init function
      dark_InitVulkan(app);
   }

   app->pWindow = glfwCreateWindow(app->windowSizeX, app->windowSizeY, app->pName, NULL, NULL);
   glfwMakeContextCurrent(app->pWindow);

   if(DARKNESS_USE_OPENGL & app->flags)
   {
      if (GLEW_OK != glewInit())
      {
	 goto EXIT_ERROR_0x03;
      }   
   }

   InitGraphicsCommands(app);

   /// TODO :: Remove this
   dark_Vertex2F left = { -1, -1 };
   dark_Vertex2F right = { 1, -1 };
   dark_Vertex2F up = { 0, 1 };

   while(1)
   {
      dark_ClearScreen(app);

      dark_DrawTriangle(left, right, up);

      dark_SwapBuffers(app);
      glfwPollEvents();

      if (glfwWindowShouldClose(app->pWindow) || app->flags & DARKNESS_START_STOP)
      {
	 goto LOOP_EXIT;
      }
   }
LOOP_EXIT:
   
   return 0x0;

EXIT_ERROR_0x03:
   /// TODO :: Cleanup this
   free(app->pName);
   free(app->pEngineName);
   app->windowSizeX = 0;
   app->windowSizeY = 0;
   glfwDestroyWindow(app->pWindow);
EXIT_ERROR_0x02:
   glfwTerminate();
EXIT_ERROR_0x01:
   return -0x1;
}
