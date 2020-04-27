#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H

#include "OrbitalBody.h"
#include "Renderer.h"

namespace solarsystem {
  extern OrbitalBody* sun;

  void Init();

  void Draw(renderer::Shader shader);
}

#endif
