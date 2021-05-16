#include<stdio.h>
#include"Engine/Darkness.h"

struct dks_Info dks;


int main(int arc, char** arv)
{
   if (dks_InitDarkness(arc, arv, &dks)) {
      return -0x1;
   }
   
   return 0x0;
}
