#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int MAJOR_VERSION = 3;
const int MINOR_VERSION = 1;

void DrawFrame(SDL_Window* window);

int main(int argc, char** argv) {
  // init SDL2
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "Could not initialize SDL: " << SDL_GetError() << std::endl;
    return EXIT_FAILURE;
  }

  // create SDL window
  SDL_Window *window = SDL_CreateWindow(
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
      return EXIT_FAILURE;
  }

  // init GLEW
  glewExperimental = GL_TRUE;
  GLenum glewError = glewInit();
  if (glewError != GLEW_OK) {
    std::cout << "Could not initialize GLEW: " << 
      glewGetErrorString(glewError) << std::endl;
    return EXIT_FAILURE;
  }

  // main program loop
  bool programEnd = false;
  SDL_Event e;
  while (!programEnd) {
    DrawFrame(window);
    // poll SDL events
    const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
    while (SDL_PollEvent(&e) != 0) {
      // terminate the program if the exit button or escape key is pressed
      if (e.type == SDL_QUIT || keyboardState[SDL_SCANCODE_ESCAPE]) {
        programEnd = true;
      }
    }
  }

  // cleanup
  SDL_DestroyWindow(window);
  SDL_Quit();

  return EXIT_SUCCESS;
}

void DrawFrame(SDL_Window* window) {
  glClearColor(0, 0, 0, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  SDL_GL_SwapWindow(window);
}
