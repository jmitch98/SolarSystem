#include "Shader.h"
#include "Renderer.h"

namespace renderer {
  Shader::Shader(const char* vertexFile, const char* fragmentFile) {
    char* vertexCode = 0;
    char* fragmentCode = 0;

    // read shader files into buffers
    ReadFileToBuffer(vertexFile, &vertexCode);
    ReadFileToBuffer(fragmentFile, &fragmentCode);

    // compile shaders
    unsigned int vertexShader, fragmentShader;
    int success;
    char log[512];

    // vertex shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexCode, NULL);
    glCompileShader(vertexShader);

    // check for vertex compilation errors
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(vertexShader, 512, NULL, log);
      std::cout << "Could not compile vertex shader: " <<
        log << std::endl;
    }

    // fragment shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentCode, NULL);
    glCompileShader(fragmentShader);

    // check for fragment compilation errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(fragmentShader, 512, NULL, log);
      std::cout << "Could not compile fragment shader: " <<
        log << std::endl;
    }

    // create the shader program
    this->id = glCreateProgram();
    glAttachShader(this->id, vertexShader);
    glAttachShader(this->id, fragmentShader);
    glLinkProgram(this->id);

    // check for linking errors
    glGetProgramiv(this->id, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(this->id, 512, NULL ,log);
      std::cout << "Error linking shaders: " <<
        log << std::endl;
    }

    // cleanup
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    free(vertexCode);
    free(fragmentCode);
  }

  void Shader::useProgram() {
    glUseProgram(this->id);
  }
}