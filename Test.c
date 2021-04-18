#include"Engine/Darkness.h"

dark_Application _appInfo;

int Main(int arc, char** arv)
{
   _appInfo.flags |= DARKNESS_START_STOP;

   if (0x0 != dark_InitDarkness(&_appInfo, arc, arv))
   {
      goto EXIT_0x1;
   }

EXIT_0x1:
   return 0x0;
}
