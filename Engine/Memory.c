#include<stdlib.h>

/// TODO :: In the future a custom memory allocator should be implemented

void* darkMalloc(size_t bytes)
{
   return malloc(bytes);
}

void darkFree(void* ptr)
{
   free(ptr);
}
