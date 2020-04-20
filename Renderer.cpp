#include "Renderer.h"

namespace renderer {
SDL_Window* window;

float vertices[] = {
    -0.5f, -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,
    -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f,  0.5f,
    -0.5f, 0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,
    -0.5f, -0.5f, 0.5f,  -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f,  -0.5f, 0.5f,  0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,  0.5f,  -0.5f, 0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f,
    0.5f,  -0.5f, 0.5f,  0.5f,  0.5f,  0.5f,  -0.5f, -0.5f, -0.5f, 0.5f,  -0.5f,
    -0.5f, 0.5f,  -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f,
    -0.5f, -0.5f, -0.5f, 0.5f,  -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  -0.5f};

unsigned int indices[] = {0, 1, 3, 1, 2, 3};

unsigned int VBO;
unsigned int VAO;
unsigned int EBO;
Shader* s;
Model* m;

// camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

// mouse
bool firstMouse = true;
float lastX = SCREEN_WIDTH / 2.0f;
float lastY = SCREEN_HEIGHT / 2.0f;
float yaw = -90.0f;
float pitch = 0.0f;

// time tracking
float deltaTime = 0.0f;
float lastFrame = 0.0f;

void Init() {
  // init SDL2
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "Could not initialize SDL: " << SDL_GetError() << std::endl;
  }

  // create SDL window
  window = SDL_CreateWindow("Solar System", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
                            SDL_WINDOW_OPENGL);

  // check for window creation errors
  if (window == NULL) {
    std::cout << "Could not create SDL window: " << SDL_GetError() << std::endl;
  }

  // create SDL OpenGL context
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, MAJOR_VERSION);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, MINOR_VERSION);

  SDL_GLContext glContext = SDL_GL_CreateContext(window);
  if (!glContext) {
    std::cout << "Could not create OpenGL context for SDL: " << SDL_GetError()
              << std::endl;
  }

  // set SDL to relative mouse mode
  if (SDL_SetRelativeMouseMode(SDL_TRUE) < 0) {
    std::cout << "Could not enable SDL relative mouse mode:" << SDL_GetError()
              << std::endl;
  }

  // init GLEW
  glewExperimental = GL_TRUE;
  GLenum glewError = glewInit();
  if (glewError != GLEW_OK) {
    std::cout << "Could not initialize GLEW: " << glewGetErrorString(glewError)
              << std::endl;
  }

  s = new Shader("./assets/shaders/shader.vert",
                 "./assets/shaders/shader.frag");

  m = new Model("./assets/models/teapot.obj");
}

void DrawFrame() {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  s->useProgram();

  // the model matrix
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::scale(model, glm::vec3(0.5, 0.5, 0.5));
  model = glm::translate(model, glm::vec3(0, -1.0f, 0));

  // the view matrix (and camera movement)
  glm::mat4 view;
  view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

  // the projection matrix
  glm::mat4 projection;
  projection = glm::perspective(
      glm::radians(45.0f),
      static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT),
      0.1f, 100.0f);

  // send matrices to the shader
  int modelLoc = glGetUniformLocation(s->id, "model");
  int viewLoc = glGetUniformLocation(s->id, "view");
  int projLoc = glGetUniformLocation(s->id, "projection");

  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
  glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

  m->Draw(*s);

  // update time
  float currentFrame = SDL_GetTicks() / 1000.0f;
  deltaTime = currentFrame - lastFrame;
  lastFrame = currentFrame;

  SDL_GL_SwapWindow(window);
}

void Destroy() {
  delete s;
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void ReadFileToBuffer(const char* filename, char** buffer) {
  FILE* f = fopen(filename, "rb");
  int16_t length;

  if (f) {
    fseek(f, 0, SEEK_END);
    length = ftell(f);
    fseek(f, 0, SEEK_SET);
    *buffer = reinterpret_cast<char*>(malloc(length + 1));

    if (buffer) {
      fread(*buffer, 1, length, f);
    }

    fclose(f);
    (*buffer)[length] = '\0';
  }
}

void HandleMouseInput(double xOffset, double yOffset) {
  yOffset *= -1;

  float sensitivity = 0.05f;
  xOffset *= sensitivity;
  yOffset *= sensitivity;

  yaw += xOffset;
  pitch += yOffset;

  if (pitch > 89.0f) pitch = 89.0f;
  if (pitch < -89.0f) pitch = -89.0f;

  glm::vec3 direction;
  direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  direction.y = sin(glm::radians(pitch));
  direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  cameraFront = glm::normalize(direction);
}
}  // namespace renderer
