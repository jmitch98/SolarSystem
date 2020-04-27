#include "Renderer.h"

#include "SolarSystem.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace renderer {
SDL_Window* window;
Shader* s;
solarsystem::OrbitalBody* earth;
solarsystem::OrbitalBody* moon;
unsigned int texture;
unsigned int moonTexture;

// camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

// view and projection matrices
glm::mat4 view;
glm::mat4 projection;

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
  glEnable(GL_DEPTH_TEST);

  s = new Shader("./assets/shaders/shader.vert",
                 "./assets/shaders/shader.frag");
}

void DrawFrame() {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  s->useProgram();

  solarsystem::Draw(*s);

  // update time
  float currentFrame = SDL_GetTicks() / 1000.0f;
  deltaTime = currentFrame - lastFrame;
  lastFrame = currentFrame;

  SDL_GL_SwapWindow(window);
}

void Destroy() {
  delete s;
  delete earth;
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

unsigned int CreateTexture(const char* texturePath) {
  unsigned int texture;

  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  int width, height, nrChannels;
  unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
  if (data) {
    GLenum format;
    if (nrChannels == 1) {
      format = GL_RED;
    } else if (nrChannels == 3) {
      format = GL_RGB;
    } else if (nrChannels == 4) {
      format = GL_RGBA;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "Failed to load texture" << std::endl;
  }
  stbi_image_free(data);

  return texture;
}
}  // namespace renderer
