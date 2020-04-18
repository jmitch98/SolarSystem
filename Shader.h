#ifndef SHADER_H
#define SHADER_H

namespace renderer {
/**
 * Shader class for the renderer.
 */
class Shader {
 private:
  /**
   * The OpenGL shader ID.
   */
  unsigned int id;

 public:
  /**
   * Creates a new shader given the file location
   * of a vertex shader and a fragment shader.
   * @param vertexFile The vertex shader source
   * @param fragmentFile The fragment shader source
   */
  Shader(const char* vertexFile, const char* fragmentFile);

  /**
   * Calls glUseProgram for the shader program.
   */
  void useProgram();
};

}  // namespace renderer

#endif
