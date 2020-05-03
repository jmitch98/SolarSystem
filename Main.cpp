#include "Renderer.h"
#include "SolarSystem.h"

struct KeyboardMouseStatus {
  bool forward = false;
  bool backward = false;
  bool left = false;
  bool right = false;
  bool rightMouseDown = false;
};

KeyboardMouseStatus keyboardMouseStatus;

void UpdateKeyboardState(SDL_Event* e, KeyboardMouseStatus* ks);

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

      if (e.type == SDL_MOUSEBUTTONDOWN &&
          e.button.button == SDL_BUTTON_RIGHT) {
        keyboardMouseStatus.rightMouseDown = true;
      } else if (e.type == SDL_MOUSEBUTTONUP &&
                 e.button.button == SDL_BUTTON_RIGHT) {
        keyboardMouseStatus.rightMouseDown = false;
      }

      if (e.type == SDL_MOUSEMOTION && keyboardMouseStatus.rightMouseDown) {
        renderer::HandleMouseInput(e.motion.xrel, e.motion.yrel);
      }

      if (e.type == SDL_MOUSEWHEEL) {
        if (e.wheel.y == 1) {
          renderer::cameraDistanceFromCenter -= 1.0f;
        } else if (e.wheel.y == -1) {
          renderer::cameraDistanceFromCenter += 1.0f;
        }

        renderer::HandleMouseInput(0.0f, 0.0f);
      }

      if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_e) {
        renderer::yaw = -90.0f;
        renderer::pitch = 0.0f;
        if (renderer::programMode == renderer::MODE::SOLARSYSTEM) {
          renderer::programMode = renderer::MODE::COMPARISON;
          std::cout << "Switched to comparison mode" << std::endl;
          renderer::cameraPos = glm::vec3(800.0f, 800.0f, 10.0f);
        } else {
          renderer::programMode = renderer::MODE::SOLARSYSTEM;
          renderer::cameraPos = glm::vec3(0.0f, 0.0f, 10.0f);
          std::cout << "Switched to solar system mode" << std::endl;
        }
      }

      if (e.type == SDL_KEYDOWN) {
        SDL_Keycode code = e.key.keysym.sym;
        switch (code) {
          case SDLK_1: solarsystem::OB2 = solarsystem::compMercury; break;
          case SDLK_2: solarsystem::OB2 = solarsystem::compVenus; break;
          case SDLK_3: solarsystem::OB2 = solarsystem::compEarth; break;
          case SDLK_4: solarsystem::OB2 = solarsystem::compMars; break;
          case SDLK_5: solarsystem::OB2 = solarsystem::compJupiter; break;
          case SDLK_6: solarsystem::OB2 = solarsystem::compSaturn; break;
          case SDLK_7: solarsystem::OB2 = solarsystem::compUranus; break;
          case SDLK_8: solarsystem::OB2 = solarsystem::compNeptune; break;
        }
      }

      UpdateKeyboardState(&e, &keyboardMouseStatus);
    }

    if (keyboardMouseStatus.forward) {
      renderer::cameraPos += cameraSpeed * renderer::cameraFront;
    }

    if (keyboardMouseStatus.backward) {
      renderer::cameraPos -= cameraSpeed * renderer::cameraFront;
    }

    if (keyboardMouseStatus.left) {
      renderer::cameraPos -= glm::normalize(glm::cross(renderer::cameraFront,
                                                       renderer::cameraUp)) *
                             cameraSpeed;
    }

    if (keyboardMouseStatus.right) {
      renderer::cameraPos += glm::normalize(glm::cross(renderer::cameraFront,
                                                       renderer::cameraUp)) *
                             cameraSpeed;
    }
  }

  // cleanup
  renderer::Destroy();

  return EXIT_SUCCESS;
}

void UpdateKeyboardState(SDL_Event* e, KeyboardMouseStatus* ks) {
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
