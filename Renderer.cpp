#include "Renderer.h"

namespace renderer {
  SDL_Window *window;

  float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f,  0.5f, 0.0f
  };  
  unsigned int VBO;
  unsigned int VAO;
  Shader* s;
  
  void Init() {
    // init SDL2
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      std::cout << "Could not initialize SDL: " << SDL_GetError() << std::endl;
    }

    // create SDL window
    window = SDL_CreateWindow(
      "Solar System",
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      SCREEN_WIDTH,
      SCREEN_HEIGHT,
      SDL_WINDOW_OPENGL
    );

    // check for window creation errors
    if (window == NULL) {
      std::cout << "Could not create SDL window: " << 
        SDL_GetError() << std::endl;
    }

    // create SDL OpenGL context
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, 
      SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, MAJOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, MINOR_VERSION);

    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
      std::cout << "Could not create OpenGL context for SDL: " <<
        SDL_GetError() << std::endl;
    }

    // init GLEW
    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
      std::cout << "Could not initialize GLEW: " << 
        glewGetErrorString(glewError) << std::endl;
    }

    // gl testing
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    s = new Shader("shader.vert", "shader.frag");
  }

  void DrawFrame() {
    glClearColor(0, 0, 0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    s->useProgram();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    SDL_GL_SwapWindow(window);
  }

  void Destroy() {
    delete s;
    SDL_DestroyWindow(window);
    SDL_Quit();
  }

  void ReadFileToBuffer(const char* filename, char** buffer) {
    FILE *f = fopen(filename, "rb");
    long length;
    
    if (f) {
      fseek(f, 0, SEEK_END);
      length = ftell(f);
      fseek(f, 0, SEEK_SET);
      *buffer = (char*) malloc(length + 1);

      if (buffer) {
        fread(*buffer, 1, length, f);
      }

      fclose(f);
      (*buffer)[length] = '\0';
    }
  }
}
