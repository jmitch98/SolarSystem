#include "Renderer.h"

namespace renderer {
  SDL_Window *window;
  
  void Init() {
    // init SDL2
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      std::cout << "Could not initialize SDL: " << SDL_GetError() << std::endl;
    }

    // create SDL window
    window = SDL_CreateWindow(
      "Solar System",
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      SCREEN_WIDTH,
      SCREEN_HEIGHT,
      SDL_WINDOW_OPENGL
    );

    // check for window creation errors
    if (window == NULL) {
      std::cout << "Could not create SDL window: " << 
        SDL_GetError() << std::endl;
    }

    // create SDL OpenGL context
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, 
      SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, MAJOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, MINOR_VERSION);

    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
      std::cout << "Could not create OpenGL context for SDL: " <<
        SDL_GetError() << std::endl;
    }

    // init GLEW
    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
      std::cout << "Could not initialize GLEW: " << 
        glewGetErrorString(glewError) << std::endl;
    }
  }

  void DrawFrame() {
    glClearColor(0, 0, 0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);
  }

  void Destroy() {
    SDL_DestroyWindow(window);
    SDL_Quit();
  }
}