#include<stdio.h>
#include"Engine/Darkness.h"

dks_Info dks;


int main(int arc, char** arv)
{
   printf("%lu\n", sizeof(dks_Info));

   if (dks_InitDarkness(arc, arv, &dks)) {
      return -0x1;
   }
   
   return 0x0;
}
