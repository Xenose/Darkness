#ifndef __darkness_graphics_header__
#define __darkness_graphics_header__

#include"Types.h"

extern int InitGraphicsCommands(dark_Application* app);

/// Pointers for either the vulkan or gl implimentation
extern void (*dark_ClearScreen)(dark_Application* app);
extern void (*dark_SwapBuffers)(dark_Application* app);
extern void (*dark_DrawTriangle)(dark_Vertex2F left, dark_Vertex2F right, dark_Vertex2F up);

#endif //__darkness_graphics_header__
