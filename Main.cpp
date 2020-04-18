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
    const float cameraSpeed = 2.5f * renderer::deltaTime;
    const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
    while (SDL_PollEvent(&e) != 0) {
      // conditions to quit program
      if (e.type == SDL_QUIT || keyboardState[SDL_SCANCODE_ESCAPE])
        programEnd = true;
      if (keyboardState[SDL_SCANCODE_W])
        renderer::cameraPos += cameraSpeed * renderer::cameraFront;
      if (keyboardState[SDL_SCANCODE_S])
        renderer::cameraPos -= cameraSpeed * renderer::cameraFront;
      if (keyboardState[SDL_SCANCODE_A])
        renderer::cameraPos -= glm::normalize(glm::cross(renderer::cameraFront,
                                                         renderer::cameraUp)) *
                               cameraSpeed;
      if (keyboardState[SDL_SCANCODE_D])
        renderer::cameraPos += glm::normalize(glm::cross(renderer::cameraFront,
                                                         renderer::cameraUp)) *
                               cameraSpeed;
    }
  }

  // cleanup
  renderer::Destroy();

  return EXIT_SUCCESS;
}
