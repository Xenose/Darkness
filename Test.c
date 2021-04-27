#include<stdio.h>
#include<math.h>
#include"Engine/Darkness.h"

darkApplication app;

void MainLoop(void)
{
}

int Main(int arc, char** arv)
{
   float a = 4.0;
   app.EngineLoop = &MainLoop;

   printf("%F\n", a);

   if (0x0 != darkInitDarkness(&app, arc, arv))
   {
      goto EXIT_0x1;
   }

EXIT_0x1:
   return 0x0;
}
