#ifndef ORBITALBODY_H
#define ORBITALBODY_H

#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Renderer.h"
#include "Shader.h"

namespace solarsystem {
class OrbitalBody {
 public:
  glm::vec3 position;
  glm::vec3 scale;
  glm::vec3 rotation;

  OrbitalBody(const char* modelPath);
  ~OrbitalBody();

  void SetMeshTexture(unsigned int textureID, unsigned int meshID);

  renderer::Model* GetModel();

  void Draw(renderer::Shader shader);

  void AddChild(OrbitalBody* orbitalBody);

  void SetParent(OrbitalBody* orbitalBody);

 private:
  OrbitalBody* parent = nullptr;
  std::vector<OrbitalBody*> children;
  float apogee;
  float parogee;
  float orbitalVelocity;
  float rotationalVelocity;
  renderer::Model* model;
};
}  // namespace solarsystem

#endif
