#include "SolarSystem.h"

namespace solarsystem {
  OrbitalBody* sun;

  void Init() {
    // the sun
    sun = new OrbitalBody("./assets/models/sun.obj");
    sun->position = glm::vec3(0.0f, 0.0f, 0.0f);
    sun->rotation = glm::vec3(1.0f, 1.0f, 1.0f);
    sun->scale = glm::vec3(0.002f, 0.002f, 0.002f);
    unsigned int sunTexture = renderer::CreateTexture("./assets/textures/sun.png");
    sun->GetModel()->meshes[0].SetTexture(sunTexture);
  }

  void Draw(renderer::Shader shader) {
    sun->Draw(shader);
  }
}