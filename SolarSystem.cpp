#include "SolarSystem.h"

namespace solarsystem {
OrbitalBody* sun;
OrbitalBody* earth;
OrbitalBody* mercury;
OrbitalBody* venus;
OrbitalBody* mars;
OrbitalBody* jupiter;
OrbitalBody* saturn;
OrbitalBody* uranus;
OrbitalBody* neptune;

const float simulationSpeed = 3600 * 24.0f;

void Init() {
  // the sun
  const float sunScale = 0.002f;
  sun = new OrbitalBody("./assets/models/sun.obj");
  sun->position = glm::vec3(0.0f, 0.0f, 0.0f);
  sun->rotation = glm::vec3(1.0f, 1.0f, 1.0f);
  sun->scale = glm::vec3(sunScale, sunScale, sunScale);
  sun->rotationalVelocity = 0.0f;
  unsigned int sunTexture =
      renderer::CreateTexture("./assets/textures/sun.png");
  sun->GetModel()->meshes[0].SetTexture(sunTexture);

  // mercury
  mercury = new OrbitalBody("./assets/models/mercury.obj", KM_TO_AU(50400000),
                            KM_TO_AU(47.4f * simulationSpeed), 0.001f, sun);
  mercury->scale = glm::vec3(sunScale, sunScale, sunScale);
  unsigned int mercuryTexture =
      renderer::CreateTexture("./assets/textures/mercury.png");
  mercury->GetModel()->meshes[0].SetTexture(mercuryTexture);

  // venus
  venus = new OrbitalBody("./assets/models/venus.obj", KM_TO_AU(108000000),
                          KM_TO_AU(35.0f * simulationSpeed), 0.001f, sun);
  venus->scale = glm::vec3(sunScale, sunScale, sunScale);
  unsigned int venusTexture =
      renderer::CreateTexture("./assets/textures/venus.png");
  venus->GetModel()->meshes[0].SetTexture(venusTexture);

  // earth
  earth = new OrbitalBody("./assets/models/earth.obj", KM_TO_AU(151000000),
                          KM_TO_AU(29.8f * simulationSpeed), 0.001f, sun);
  earth->scale = glm::vec3(sunScale, sunScale, sunScale);
  unsigned int earthTexture =
      renderer::CreateTexture("./assets/textures/earth.png");
  earth->GetModel()->meshes[0].SetTexture(earthTexture);

  // mars
  mars = new OrbitalBody("./assets/models/mars.obj", KM_TO_AU(217000000),
                         KM_TO_AU(24.1 * simulationSpeed), 0.001f, sun);
  mars->scale = glm::vec3(sunScale, sunScale, sunScale);
  unsigned int marsTexture =
      renderer::CreateTexture("./assets/textures/mars.png");
  mars->GetModel()->meshes[0].SetTexture(marsTexture);

  // jupiter
  jupiter = new OrbitalBody("./assets/models/jupiter.obj", KM_TO_AU(776000000 / 4),
                            KM_TO_AU(13.1 * simulationSpeed), 0.001f, sun);
  jupiter->scale = glm::vec3(sunScale, sunScale, sunScale);
  unsigned int jupiterTexture =
      renderer::CreateTexture("./assets/textures/jupiter.png");
  jupiter->GetModel()->meshes[0].SetTexture(jupiterTexture);

  // saturn
  saturn = new OrbitalBody("./assets/models/Saturn.obj", KM_TO_AU(1500000000 / 4),
                           KM_TO_AU(9.7 * simulationSpeed), 0.001f, sun);
  saturn->scale = glm::vec3(sunScale, sunScale, sunScale);
  unsigned int saturnTexture1 =
      renderer::CreateTexture("./assets/textures/Saturn_Planet.png");
  unsigned int saturnTexture2 =
      renderer::CreateTexture("./assets/textures/Saturn_Rings_Top.png");
  saturn->GetModel()->meshes[0].SetTexture(saturnTexture1);
  saturn->GetModel()->meshes[1].SetTexture(saturnTexture2);
  saturn->GetModel()->meshes[2].SetTexture(saturnTexture2);

  // uranus
  uranus = new OrbitalBody("./assets/models/uranus.obj", KM_TO_AU(2960000000 / 4),
                           KM_TO_AU(6.8 * simulationSpeed), 0.001f, sun);
  uranus->scale = glm::vec3(sunScale, sunScale, sunScale);
  unsigned int uranusTexture =
      renderer::CreateTexture("./assets/textures/uranus.png");
  uranus->GetModel()->meshes[0].SetTexture(uranusTexture);

  // neptune
  neptune = new OrbitalBody("./assets/models/neptune.obj", KM_TO_AU(4480000000 / 4),
                           KM_TO_AU(6.8 * simulationSpeed), 0.001f, sun);
  neptune->scale = glm::vec3(sunScale, sunScale, sunScale);
  unsigned int neptuneTexture =
      renderer::CreateTexture("./assets/textures/neptune.png");
  neptune->GetModel()->meshes[0].SetTexture(neptuneTexture);
}

void Draw(renderer::Shader shader) { sun->Draw(shader); }
}  // namespace solarsystem