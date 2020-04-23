#include "Mesh.h"

#include <iostream>

namespace renderer {
Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices) {
  this->vertices = vertices;
  this->indices = indices;

  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);

  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0],
               GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
               &indices[0], GL_STATIC_DRAW);

  // vertex positions
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        reinterpret_cast<void*>(0));
  // vertex normals
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        reinterpret_cast<void*>(offsetof(Vertex, Normal)));
  // vertex texture coords
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(
      2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
      reinterpret_cast<void*>(offsetof(Vertex, TextureCoordinates)));

  glBindVertexArray(0);
}

void Mesh::Draw(Shader shader) {
  glBindVertexArray(vao);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

void Mesh::SetTexture(unsigned int texture) {
  this->texture = texture;
}
}  // namespace renderer
