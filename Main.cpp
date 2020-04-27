#include "Renderer.h"
#include "SolarSystem.h"

struct KeyboardStatus {
  bool forward = false;
  bool backward = false;
  bool left = false;
  bool right = false;
};

KeyboardStatus keyboardStatus;

void UpdateKeyboardState(SDL_Event* e, KeyboardStatus* ks);

int main(int argc, char** argv) {
  // init the SDL/OpenGL renderer
  renderer::Init();

  solarsystem::Init();

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
      if (e.type == SDL_QUIT || keyboardState[SDL_SCANCODE_ESCAPE]) {
        programEnd = true;
      }
      if (e.type == SDL_MOUSEMOTION) {
        renderer::HandleMouseInput(e.motion.xrel, e.motion.yrel);
      }

      UpdateKeyboardState(&e, &keyboardStatus);
    }

    if (keyboardStatus.forward) {
      renderer::cameraPos += cameraSpeed * renderer::cameraFront;
    }

    if (keyboardStatus.backward) {
      renderer::cameraPos -= cameraSpeed * renderer::cameraFront;
    }

    if (keyboardStatus.left) {
      renderer::cameraPos -= glm::normalize(glm::cross(renderer::cameraFront,
                                                       renderer::cameraUp)) *
                             cameraSpeed;
    }

    if (keyboardStatus.right) {
      renderer::cameraPos += glm::normalize(glm::cross(renderer::cameraFront,
                                                       renderer::cameraUp)) *
                             cameraSpeed;
    }
  }

  // cleanup
  renderer::Destroy();

  return EXIT_SUCCESS;
}

void UpdateKeyboardState(SDL_Event* e, KeyboardStatus* ks) {
  // key down
  if (e->type == SDL_KEYDOWN) {
    SDL_Keycode code = e->key.keysym.sym;
    if (code == SDLK_w) ks->forward = true;
    if (code == SDLK_s) ks->backward = true;
    if (code == SDLK_a) ks->left = true;
    if (code == SDLK_d) ks->right = true;
  }

  // key up
  if (e->type == SDL_KEYUP) {
    SDL_Keycode code = e->key.keysym.sym;
    if (code == SDLK_w) ks->forward = false;
    if (code == SDLK_s) ks->backward = false;
    if (code == SDLK_a) ks->left = false;
    if (code == SDLK_d) ks->right = false;
  }
}
