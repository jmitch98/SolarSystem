#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
#include "Shader.h"

#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <assimp/Importer.hpp>

#include "Renderer.h"

namespace renderer {
/**
 * Loads and creates a new model.
 * @param filePath The file location of the model.
 */
class Model {
 public:
  Model(const char* filePath);

  /**
   * Draws the model (and thus all meshes within it)
   * @param shader The shader to draw all the model's
   * meshes with
   */
  void Draw(Shader shader);

 private:
  std::vector<Mesh> meshes;

  /**
   * Recursively processes each node in the assimp scene
   * @param node The node to process (usually starting with the root node)
   * @param scene The assimp scene the node resides in
   */
  void processSceneNode(aiNode* node, const aiScene* scene);

  /**
   * Processes an assimp mesh and adds it to the model's list of meshes
   * @param mesh The mesh to process
   * @param scene The assimp scene the mesh resides in
   * @return The prepared mesh to associate with the Model
   */
  Mesh processMesh(aiMesh* mesh, const aiScene* scene);
};
}  // namespace renderer

#endif
