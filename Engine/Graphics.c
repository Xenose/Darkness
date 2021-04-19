#include"Graphics.h"

void (*dark_ClearScreen)(dark_Application* app);
void (*dark_SwapBuffers)(dark_Application* app);
void (*dark_DrawTriangle)(dark_Vertex2F left, dark_Vertex2F right, dark_Vertex2F up);

void dark_ClearScreenGL(dark_Application* app)
{
   glClear(GL_COLOR_BUFFER_BIT);
}

void dark_SwapBuffersGL(dark_Application* app)
{
   glfwSwapBuffers(app->pWindow);
}

void dark_DrawTriangleGL(dark_Vertex2F left, dark_Vertex2F right, dark_Vertex2F up)
{
   glBegin(GL_TRIANGLES);
      glVertex2f(left.x, left.y);
      glVertex2f(right.x, right.y);
      glVertex2f(up.x, up.y);
   glEnd();
}

void dark_ClearScreenVulkan(dark_Application* app)
{
}

void dark_SwapBuffersVulkan(dark_Application* app)
{
}

void dark_DrawTriangleVulkan(dark_Vertex2F left, dark_Vertex2F right, dark_Vertex2F up)
{
}

int InitGraphicsCommands(dark_Application* app)
{
   if (DARKNESS_USE_OPENGL & app->flags)
   {
      dark_ClearScreen = &dark_ClearScreenGL;
      dark_SwapBuffers = &dark_SwapBuffersGL;
      dark_DrawTriangle = &dark_DrawTriangleGL;
      return 0x0;
   }

   dark_ClearScreen = &dark_ClearScreenVulkan;
   dark_SwapBuffers = &dark_SwapBuffersVulkan;
   dark_DrawTriangle = &dark_DrawTriangleVulkan;
   return 0x0;
}
