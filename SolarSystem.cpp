#include "SolarSystem.h"

namespace solarsystem {
// solar system planets
OrbitalBody* sun;
OrbitalBody* earth;
OrbitalBody* moon;
OrbitalBody* mercury;
OrbitalBody* venus;
OrbitalBody* mars;
OrbitalBody* jupiter;
OrbitalBody* saturn;
OrbitalBody* uranus;
OrbitalBody* neptune;
OrbitalBody* pluto;

// comparison mode planets
OrbitalBody* compMercury;
OrbitalBody* compVenus;
OrbitalBody* compEarth;
OrbitalBody* compMars;
OrbitalBody* compJupiter;
OrbitalBody* compSaturn;
OrbitalBody* compUranus;
OrbitalBody* compNeptune;
OrbitalBody* compMoon;
OrbitalBody* compSun;
OrbitalBody* compPluto;

OrbitalBody* OB1;
OrbitalBody* OB2;

float simulationSpeedMultiplier = 1.0f;
float simulationSpeed = 3600 * 24.0f;

void Init() {
  // the sun
  const float sunScale = 0.005f;
  float compBaseScale = 0.002f;

  sun = new OrbitalBody("./assets/models/sun.obj");
  sun->position = glm::vec3(0.0f, 0.0f, 0.0f);
  sun->rotation = glm::vec3(1.0f, 1.0f, 1.0f);
  sun->scale = glm::vec3(sunScale, sunScale, sunScale);
  sun->rotationalVelocity = 0.0f;
  unsigned int sunTexture =
      renderer::CreateTexture("./assets/textures/sun.png");
  sun->GetModel()->meshes[0].SetTexture(sunTexture);

  compSun = new OrbitalBody(sun);
  compSun->position = glm::vec3(1200.0f, 800.0f, 0.0f);
  compSun->scale = glm::vec3(compBaseScale * 285);

  // mercury
  float terrestrialScale = 0.25 * sunScale;
  mercury = new OrbitalBody("./assets/models/mercury.obj", KM_TO_AU(50400000),
                            172.8, 10.892, sun);
  mercury->scale =
      glm::vec3(terrestrialScale, terrestrialScale, terrestrialScale);
  unsigned int mercuryTexture =
      renderer::CreateTexture("./assets/textures/mercury.png");
  mercury->GetModel()->meshes[0].SetTexture(mercuryTexture);

  compMercury = new OrbitalBody(mercury);
  compMercury->position = glm::vec3(805.0f, 800.0f, 0.0f);
  compMercury->scale = glm::vec3(compBaseScale);
  OB2 = compMercury;

  // venus
  venus = new OrbitalBody("./assets/models/venus.obj", KM_TO_AU(108000000),
                          126.072, 6.52, sun);
  venus->scale =
      glm::vec3(terrestrialScale, terrestrialScale, terrestrialScale);
  unsigned int venusTexture =
      renderer::CreateTexture("./assets/textures/venus.png");
  venus->rotation = glm::vec3(0.0f, 1.0f, 0.0f);
  venus->GetModel()->meshes[0].SetTexture(venusTexture);

  compVenus = new OrbitalBody(venus);
  compVenus->position = glm::vec3(805.0f, 800.0f, 0.0f);
  compVenus->scale = glm::vec3(2.48f * compBaseScale);

  // earth
  earth = new OrbitalBody("./assets/models/earth.obj", KM_TO_AU(151000000),
                          28.08, 1609.3, sun);
  earth->scale =
      glm::vec3(terrestrialScale, terrestrialScale, terrestrialScale);
  unsigned int earthTexture =
      renderer::CreateTexture("./assets/textures/earth.png");
  earth->GetModel()->meshes[0].SetTexture(earthTexture);
  earth->rotation = glm::vec3(0.0f, 1.0f, 0.0f);

  compEarth = new OrbitalBody(earth);
  compEarth->position = glm::vec3(795.0f, 800.0f, 0.0f);
  compEarth->scale = glm::vec3(compBaseScale * 2.61f);
  OB1 = compEarth;

  // mars
  mars = new OrbitalBody("./assets/models/mars.obj", KM_TO_AU(217000000), 86.4,
                         868, sun);
  mars->scale = glm::vec3(terrestrialScale, terrestrialScale, terrestrialScale);
  unsigned int marsTexture =
      renderer::CreateTexture("./assets/textures/mars.png");
  mars->GetModel()->meshes[0].SetTexture(marsTexture);

  compMars = new OrbitalBody(mars);
  compMars->position = glm::vec3(805.0f, 800.0f, 0.0f);
  compMars->scale = glm::vec3(1.39f * compBaseScale);

  // jupiter
  float gasGiantScale = 0.5 * sunScale;
  jupiter = new OrbitalBody("./assets/models/jupiter.obj",
                            KM_TO_AU(776000000 / 2), 47.16, 43000, sun);
  jupiter->scale = glm::vec3(gasGiantScale, gasGiantScale, gasGiantScale);
  unsigned int jupiterTexture =
      renderer::CreateTexture("./assets/textures/jupiter.png");
  jupiter->GetModel()->meshes[0].SetTexture(jupiterTexture);

  compJupiter = new OrbitalBody(jupiter);
  compJupiter->position = glm::vec3(840.0f, 800.0f, 0.0f);
  compJupiter->scale = glm::vec3(29.3f * compBaseScale);

  // saturn
  saturn = new OrbitalBody("./assets/models/Saturn.obj",
                           KM_TO_AU(1500000000 / 2), 34.848, 35500, sun);
  saturn->scale = glm::vec3(gasGiantScale, gasGiantScale, gasGiantScale);
  unsigned int saturnTexture1 =
      renderer::CreateTexture("./assets/textures/Saturn_Planet.png");
  unsigned int saturnTexture2 =
      renderer::CreateTexture("./assets/textures/Saturn_Rings_Top.png");
  saturn->GetModel()->meshes[0].SetTexture(saturnTexture1);
  saturn->GetModel()->meshes[1].SetTexture(saturnTexture2);
  saturn->GetModel()->meshes[2].SetTexture(saturnTexture2);

  compSaturn = new OrbitalBody(saturn);
  compSaturn->position = glm::vec3(860.0f, 800.0f, 0.0f);
  compSaturn->scale = glm::vec3(24.7f * compBaseScale);

  // uranus
  uranus = new OrbitalBody("./assets/models/uranus.obj",
                           KM_TO_AU(2960000000 / 2), 24.48, 24500, sun);
  uranus->scale = glm::vec3(gasGiantScale, gasGiantScale, gasGiantScale);
  unsigned int uranusTexture =
      renderer::CreateTexture("./assets/textures/uranus.png");
  uranus->GetModel()->meshes[0].SetTexture(uranusTexture);
  uranus->sideRotation = true;
  uranus->rotation = glm::vec3(0.0f, 1.0f, 0.0f);

  compUranus = new OrbitalBody(uranus);
  compUranus->position = glm::vec3(810.0f, 800.0f, 0.0f);
  compUranus->scale = glm::vec3(10.5f * compBaseScale);

  // neptune
  neptune = new OrbitalBody("./assets/models/neptune.obj",
                            KM_TO_AU(4480000000 / 2), 24.48, 9650, sun);
  neptune->scale = glm::vec3(gasGiantScale, gasGiantScale, gasGiantScale);
  unsigned int neptuneTexture =
      renderer::CreateTexture("./assets/textures/neptune.png");
  neptune->GetModel()->meshes[0].SetTexture(neptuneTexture);

  compNeptune = new OrbitalBody(neptune);
  compNeptune->position = glm::vec3(810.0f, 800.0f, 0.0f);
  compNeptune->scale = glm::vec3(10.02f * compBaseScale);

  // moon
  moon = new OrbitalBody("./assets/models/moon.obj", KM_TO_AU(15000000), 3.492,
                         3.6792, earth);
  moon->scale = glm::vec3(terrestrialScale * 0.3);
  unsigned int moonTexture =
      renderer::CreateTexture("./assets/textures/moon.png");
  moon->GetModel()->meshes[0].SetTexture(moonTexture);

  compMoon = new OrbitalBody(moon);
  compMoon->position = glm::vec3(805.0f, 800.0f, 0.0f);
  compMoon->scale = glm::vec3(0.712 * compBaseScale);

  // pluto
  pluto = new OrbitalBody("./assets/models/pluto.obj", KM_TO_AU(5906380000),
                          17.064, 47.18, sun);
  pluto->scale = glm::vec3(terrestrialScale);
  unsigned int plutoTexture =
      renderer::CreateTexture("./assets/textures/pluto.png");
  pluto->GetModel()->meshes[0].SetTexture(plutoTexture);

  compPluto = new OrbitalBody(pluto);
  compPluto->position = glm::vec3(805.0f, 800.0f, 0.0f);
  compPluto->scale = glm::vec3(0.488 * compBaseScale);
}

void Draw(renderer::Shader shader) {
  sun->Draw(shader);
  OB1->Draw(shader);
  OB2->Draw(shader);
}

void Destroy() { delete sun; }
}  // namespace solarsystem
