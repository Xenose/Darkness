#include"Graphics.h"

void (*dark_ClearScreen)(darkApplication* app);
void (*dark_SwapBuffers)(darkApplication* app);
void (*dark_DrawTriangle)(darkVertex2F left, darkVertex2F right, darkVertex2F up);

void dark_ClearScreenGL(darkApplication* app)
{
   glClear(GL_COLOR_BUFFER_BIT);
}

void dark_SwapBuffersGL(darkApplication* app)
{
   glfwSwapBuffers(app->pWindow);
}

void dark_DrawTriangleGL(darkVertex2F left, darkVertex2F right, darkVertex2F up)
{
   glBegin(GL_TRIANGLES);
      glVertex2f(left.x, left.y);
      glVertex2f(right.x, right.y);
      glVertex2f(up.x, up.y);
   glEnd();
}

void dark_ClearScreenVulkan(darkApplication* app)
{
}

void dark_SwapBuffersVulkan(darkApplication* app)
{
}

void dark_DrawTriangleVulkan(darkVertex2F left, darkVertex2F right, darkVertex2F up)
{
}

int InitGraphicsCommands(darkApplication* app)
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
