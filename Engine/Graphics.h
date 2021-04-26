#ifndef __darkness_graphics_header__
#define __darkness_graphics_header__

#include"Types.h"

extern int InitGraphicsCommands(darkApplication* app);

/// Pointers for either the vulkan or gl implimentation
extern void (*dark_ClearScreen)(darkApplication* app);
extern void (*dark_SwapBuffers)(darkApplication* app);
extern void (*dark_DrawTriangle)(darkVertex2F left, darkVertex2F right, darkVertex2F up);

#endif //__darkness_graphics_header__
