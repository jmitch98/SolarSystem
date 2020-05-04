#include "OrbitalBody.h"

namespace solarsystem {
OrbitalBody::OrbitalBody(const char* modelPath) {
  this->model = new renderer::Model(modelPath);
}

OrbitalBody::OrbitalBody(const char* modelPath, float distanceFromParent,
                         float orbitalVelocity, float rotationalVelocity,
                         OrbitalBody* parent) {
  this->model = new renderer::Model(modelPath);
  this->distanceFromParent = distanceFromParent;
  this->orbitalVelocity = orbitalVelocity;
  this->rotationalVelocity = rotationalVelocity;
  this->SetParent(parent);
  this->rotation = glm::vec3(0.0f, 1.0f, 0.0f);
}

OrbitalBody::OrbitalBody(OrbitalBody* ob) {
  this->model = ob->GetModel();
  this->rotation = ob->rotation;
  this->scale = ob->scale;
  this->rotationalVelocity = ob->rotationalVelocity;
}

OrbitalBody::~OrbitalBody() {
  delete model;
  for (OrbitalBody* ob : children) {
    delete ob;
  }
}

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
  parent->AddChild(this);
}

void OrbitalBody::Draw(renderer::Shader shader) {
  glm::mat4 model = glm::mat4(1.0f);

  if (parent == nullptr) {
    model = glm::translate(model, position);
  } else {
    model = glm::translate(model, parent->position);
    float posX =
        sin((SDL_GetTicks() / 1000.0f) * orbitalVelocity) * distanceFromParent;
    float posZ =
        cos((SDL_GetTicks() / 1000.0f) * orbitalVelocity) * distanceFromParent;
    position.x = posX;
    position.z = posZ;
    model = glm::translate(model, position);
  }

  model = glm::rotate(
      model,
      static_cast<float>(rotationalVelocity * (SDL_GetTicks() / 1000.0f)) *
          glm::radians(1.0f),
      rotation);
  model = glm::scale(model, scale);

  // send model matrix to the shader
  int modelLoc = glGetUniformLocation(shader.id, "model");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

  this->model->Draw(shader);

  for (OrbitalBody* ob : children) {
    ob->Draw(shader);
  }
}

renderer::Model* OrbitalBody::GetModel() { return model; }
}  // namespace solarsystem
