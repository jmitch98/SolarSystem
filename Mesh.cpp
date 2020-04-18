#include "Mesh.h"
#include <iostream>

namespace renderer {
Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
           std::vector<Texture> textures) {
  this->vertices = vertices;
  this->indices  = indices;
  this->textures = textures;

  // set up the mesh's vertex buffer
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0],
               GL_STATIC_DRAW);

  // set up the mesh's element buffer
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
               &indices[0], GL_STATIC_DRAW);

  // set up the mesh's vertex array object
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glEnableVertexAttribArray(0);

  // the part of the vertex buffer for the mesh's vertices
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        reinterpret_cast<void*>(0));

  // the part of the vertex buffer for the mesh's normals
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        reinterpret_cast<void*>(offsetof(Vertex, Normal)));

  // the part of the vertex buffer for the mesh's texture coordinates
  glVertexAttribPointer(
      2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
      reinterpret_cast<void*>(offsetof(Vertex, TextureCoordinates)));

  // bind vertex array
  glBindVertexArray(0);
}

void Mesh::Draw(Shader shader) {
  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}
}  // namespace renderer
