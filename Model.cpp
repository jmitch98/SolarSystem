#include "Model.h"

namespace renderer {
Model::Model(const char* filePath) {
  // read in the model data via assimp
  Assimp::Importer importer;
  const aiScene* scene =
      importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

  // check for import errors
  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
      !scene->mRootNode) {
    std::cout << "Error importing model via Assimp:"
              << importer.GetErrorString() << std::endl;
    return;
  }

  // begin processing the assimp scene
  processSceneNode(scene->mRootNode, scene);
}

void Model::processSceneNode(aiNode* node, const aiScene* scene) {
  // process all meshes for the node
  for (unsigned int i = 0; i < node->mNumMeshes; i++) {
    aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
    meshes.push_back(processMesh(mesh, scene));
  }

  // recursively process all meshes for this node's children
  for (unsigned int i = 0; i < node->mNumChildren; i++) {
    processSceneNode(node->mChildren[i], scene);
  }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;

  // process vertices, normals, and texture coordinates
  for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
    Vertex vertex;
    glm::vec3 vector;

    // vertices
    vector.x = mesh->mVertices[i].x;
    vector.y = mesh->mVertices[i].y;
    vector.z = mesh->mVertices[i].z;
    vertex.Position = vector;

    // normals
    if (mesh->mNormals != NULL) {
      vector.x = mesh->mNormals[i].x;
      vector.y = mesh->mNormals[i].y;
      vector.z = mesh->mNormals[i].z;
      vertex.Normal = vector;
    } else {
      vertex.Normal = glm::vec3(0.0f, 0.0f, 0.0f);
    }

    // texture coordinates
    if (mesh->mTextureCoords[0]) {
      glm::vec2 vec;
      vec.x = mesh->mTextureCoords[0][i].x;
      vec.y = mesh->mTextureCoords[0][i].y;
      vertex.TextureCoordinates = vec;
    } else {
      vertex.TextureCoordinates = glm::vec2(0.0f, 0.0f);
    }

    vertices.push_back(vertex);
  }

  // proces indices
  for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
    aiFace face = mesh->mFaces[i];
    for (unsigned int j = 0; j < face.mNumIndices; j++) {
      indices.push_back(face.mIndices[j]);
    }
  }

  return Mesh(vertices, indices);
}

void Model::Draw(Shader shader) {
  for (Mesh m : meshes) {
    m.Draw(shader);
  }
}
}  // namespace renderer
