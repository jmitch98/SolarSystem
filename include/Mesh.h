#ifndef MESH_H
#define MESH_H

#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <GL/glew.h>
#include <GL/gl.h>

#include "Shader.h"
#include "Mesh.h"

namespace renderer {
struct Vertex {
  glm::vec3 Position;
  glm::vec3 Normal;
  glm::vec2 TextureCoordinates;
};

class Mesh {
 private:
  /**
   * The OpenGL vertex buffer
   * and associated vertex array object
   * and element buffer object.
   */
  unsigned int vbo, vao, ebo, texture;

 public:
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;

  /**
   * Creates a new Mesh object.
   * @param vertices The vertices of the mesh
   * @param indices The indices of the mesh
   * @param textures The textures of the mesh
   */
  Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

  /**
   * Draws the mesh.
   * @param shader The shader used to draw the mesh.
   */
  void Draw(Shader shader);

  void SetTexture(unsigned int texture);
};

}  // namespace renderer

#endif

