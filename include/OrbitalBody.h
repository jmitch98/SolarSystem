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
  bool sideRotation = false;

  /**
   * Creates a brand new orbital body with no parents or
   * other parameters; useful for instantiating root objects like stars.
   * @param modelPath the path to the 3D model used for this object
   */
  explicit OrbitalBody(const char* modelPath);

  /**
   * Creates a brand new orbital body with common
   * startup parameters.
   * @param modelPath the path to the body's model
   * @param distaneFromParent the average distance between the object
   * and the one it orbits
   * @param orbitalVelocity how fast the object orbits its parent
   * @param rotaionalVelocity how fast the object rotates
   * @param parent the object this body orbits
   */
  OrbitalBody(const char* modelPath, float distanceFromParent,
              float orbitalVelocity, float rotationalVelocity,
              OrbitalBody* parent);

  /**
   * A very lightweight copy constructor that allows an orbital body
   * to share the same model/textures, position, scale, rotation,
   * and distance from a parent as the existing one; used for the
   * comparison mode so bodies need not have duplicates of the same models
   * and textures.
   * @param ob The OrbitalBodt to copy from
   */
  explicit OrbitalBody(OrbitalBody* ob);

  /**
   * Frees any memory allocated by the orbital body.
   */
  ~OrbitalBody();

  /**
   * Sets a mesh in this body's model to the textureID (the meshes contained
   * within an OBJ file can be viewed through an application like Blender)
   * @param textureID the OpenGL textureID
   * @param meshID the ID of this body's model mesh to assign the texture to
   */
  void SetMeshTexture(unsigned int textureID, unsigned int meshID);

  /**
   * Gets the pointer to this body's 3D model.
   * @return A pointer to a model object
   */
  renderer::Model* GetModel();

  /**
   * Draws this object's model to the screen using the specified
   * shader.
   * @param shader the OpenGL shader to use for drawing
   */
  void Draw(renderer::Shader shader);

  /**
   * Sets this body's parent (and consequently assigns this body to its
   * parent's list of children)
   */
  void SetParent(OrbitalBody* orbitalBody);

 private:
  OrbitalBody* parent = nullptr;

  /**
   * Adds a child OrbitalBody to this object
   * @param orbitalBody The child pointer to assign to this object
   */
  void AddChild(OrbitalBody* orbitalBody);

  std::vector<OrbitalBody*> children;
  renderer::Model* model;
};
}  // namespace solarsystem

#endif
