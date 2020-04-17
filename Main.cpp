#include "Renderer.h"

int main(int argc, char** argv) {
  // init the SDL/OpenGL renderer
  renderer::Init();

  // main program loop
  bool programEnd = false;
  SDL_Event e;
  while (!programEnd) {
    // draw frame from renderer
    renderer::DrawFrame();

    // poll input events
    const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
    while (SDL_PollEvent(&e) != 0) {
      // conditions to quit program
      if (e.type == SDL_QUIT || keyboardState[SDL_SCANCODE_ESCAPE]) {
        programEnd = true;
      }
    }
  }

  // cleanup
  renderer::Destroy();

  return EXIT_SUCCESS;
}
