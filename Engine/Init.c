#include<getopt.h>
#include"Utils.h"
#include"IO.h"
#include"Vulkan.h"
#include"Init.h"

/* Temporary headers */
/* End of Temporary headers */

static struct option engCliOpt[] = {
   { "dryrun",		no_argument,		0,	'd' },
   { "debug",		no_argument,		0,	'D' },
   { "opengl",		no_argument,		0,	'O' },
   { "gpu-override",	required_argument,	0,	 0  },
};

/* 
 * The parse the input args we use the getopt_long function 
 * note if ported to windows this needs to be reimplemented
 */

void dks_ParseArgs(int arc, char** arv, struct dks_Info* dks)
{
   int arg;
   int index = 0;

   while (-1 != (arg = getopt_long(arc, arv, "dDO", engCliOpt, &index))) {
      switch(arg) {
	 case 0:
	    break;
	 case 'd':
	    dks->flags |= DARKNESS_FLAG_DRYRUN;
	    dks_Puts("dryrun");
	    break;
	 case 'D':
	    dks_Puts("using debug mode");
	    break;
	 case 'O':
	    dks->flags |= DARKNESS_FLAG_USE_OPENGL;
	    dks_Puts("using opengl");
	    break;
      }
   }
}

void dks_CheckInfo(struct dks_Info* dks)
{
   if (NULL == dks->pName)
      dks->pName = dks_Crestr("No Name");

   if (NULL == dks->pEngineName)
      dks->pEngineName = dks_Crestr("Darkness");

   if (0 >= dks->windowSizeX || 0 >= dks->windowSizeY) {
      dks->windowSizeX = 1920;
      dks->windowSizeY = 1080;
   }

   if (0 == dks->version.major && 0 == dks->version.minor && 0 == dks->version.patch)
      dks->version.patch = 1;
   
   if (0 == dks->engineVersion.major && 0 == dks->engineVersion.minor && 0 == dks->engineVersion.patch)
      dks->engineVersion.patch = 1;
}

/* 
 * The main function for this engine 
 */
int dks_InitDarkness(int arc, char** arv, struct dks_Info* dks)
{
   dks_ParseArgs(arc, arv, dks);
   dks_CheckInfo(dks);

   if (GLFW_TRUE != dks_LogCall(glfwInit()))
      goto ERROR_EXIT;

   if (GLFW_TRUE != dks_LogCall(glfwVulkanSupported()))
      dks->flags |= DARKNESS_FLAG_USE_OPENGL; 
   
   if (DARKNESS_FLAG_USE_OPENGL & ~dks->flags)
      glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
   
   dks->pWindow = glfwCreateWindow(dks->windowSizeX, dks->windowSizeY, dks->pName, NULL, NULL);

   if (NULL == dks->pWindow)
      goto ERROR_TERMINATE_GLFW;

   if (0 != dks_LogCall(dks_InitVulkan(dks)))
      dks->flags |= DARKNESS_FLAG_USE_OPENGL; 

   if (DARKNESS_FLAG_USE_OPENGL & dks->flags)
      glfwMakeContextCurrent(dks->pWindow);


   if (DARKNESS_FLAG_DRYRUN & ~dks->flags) {
      while(!glfwWindowShouldClose(dks->pWindow)) {
	 glfwPollEvents();
      }
   }

   return 0x0;
ERROR_TERMINATE_GLFW:
   glfwTerminate();
ERROR_EXIT:
   return -0x1;
}
