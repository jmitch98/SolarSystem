#include "OrbitalBody.h"

namespace solarsystem {
OrbitalBody::OrbitalBody(const char* modelPath) {
  this->model = new renderer::Model(modelPath);
}

OrbitalBody::~OrbitalBody() { delete model; }

void OrbitalBody::SetMeshTexture(unsigned int textureID, unsigned int meshID) {
  model->meshes[meshID].SetTexture(textureID);

  for (OrbitalBody* ob : children) {
    delete ob;
  }
}

void OrbitalBody::AddChild(OrbitalBody* orbitalBody) {
  children.push_back(orbitalBody);
}

void OrbitalBody::SetParent(OrbitalBody* orbitalBody) {
  parent = orbitalBody;
}

void OrbitalBody::Draw(renderer::Shader shader) {
  renderer::view = glm::lookAt(renderer::cameraPos,
                               renderer::cameraPos + renderer::cameraFront,
                               renderer::cameraUp);
  renderer::projection = glm::perspective(
      glm::radians(45.0f),
      static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT),
      0.1f, 100.0f);

  glm::mat4 model = glm::mat4(1.0f);
  
  if (parent == nullptr) {
    model = glm::translate(model, position);
  } else {
    float posX = sin((SDL_GetTicks() / 1000.0f)) * 3.0f;
    float posZ = cos((SDL_GetTicks() / 1000.0f)) * 3.0f;
    position.x = posX;
    position.z = posZ;
    model = glm::translate(model, parent->position);
    model = glm::translate(model, position);
  }

  model = glm::rotate(
      model,
      static_cast<float>(10 * (SDL_GetTicks() / 1000.0f)) * glm::radians(1.0f),
      rotation);
  model = glm::scale(model, scale);

  // send model matrix to the shader
  int modelLoc = glGetUniformLocation(shader.id, "model");
  int viewLoc = glGetUniformLocation(shader.id, "view");
  int projLoc = glGetUniformLocation(shader.id, "projection");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(renderer::view));
  glUniformMatrix4fv(projLoc, 1, GL_FALSE,
                     glm::value_ptr(renderer::projection));

  this->model->Draw(shader);

  for (OrbitalBody* ob : children) {
    ob->Draw(shader);
  }
}

renderer::Model* OrbitalBody::GetModel() { return model; }
}  // namespace solarsystem