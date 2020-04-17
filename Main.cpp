#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

void PollSDLEvents();

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

  // main program loop
  bool programEnd = false;
  SDL_Event e;
  while (!programEnd) {
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