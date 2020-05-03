#ifndef ORBITALBODY_H
#define ORBITALBODY_H

#include <vector>

#include "Renderer.h"
#include "Shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace solarsystem {
class OrbitalBody {
 public:
  glm::vec3 position;
  glm::vec3 scale;
  glm::vec3 rotation;
  float distanceFromParent;
  float orbitalVelocity;
  float rotationalVelocity;

  explicit OrbitalBody(const char* modelPath);
  OrbitalBody(const char* modelPath, float distanceFromParent,
              float orbitalVelocity, float rotationalVelocity,
              OrbitalBody* parent);
  explicit OrbitalBody(OrbitalBody* ob);
  ~OrbitalBody();

  void SetMeshTexture(unsigned int textureID, unsigned int meshID);

  renderer::Model* GetModel();

  void Draw(renderer::Shader shader);

  void SetParent(OrbitalBody* orbitalBody);

 private:
  OrbitalBody* parent = nullptr;
  void AddChild(OrbitalBody* orbitalBody);
  std::vector<OrbitalBody*> children;
  renderer::Model* model;
};
}  // namespace solarsystem

#endif
