#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H

#include "OrbitalBody.h"
#include "Renderer.h"

#define AU 3.0f
#define KM_TO_AU(km) km / 16819000.0f

namespace solarsystem {
  extern OrbitalBody* sun;

  void Init();

  void Draw(renderer::Shader shader);
}

#endif
