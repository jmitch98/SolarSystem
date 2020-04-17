#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int MAJOR_VERSION = 3;
const int MINOR_VERSION = 1;

namespace renderer {
  /**
   * The main render target.
   */
  extern SDL_Window *window;

  /**
   * Initializes SDL and OpenGL.
   */
  void Init();
  
  /**
   * Draws a frame to the renderer.
   */
  void DrawFrame();

  /**
   * Frees all memory associated with the renderer.
   */
  void Destroy();
}

#endif