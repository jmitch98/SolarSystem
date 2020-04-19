#ifndef RENDERER_H
#define RENDERER_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>

#include "Model.h"
#include "Shader.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int MAJOR_VERSION = 3;
const int MINOR_VERSION = 1;

namespace renderer {
/**
 * The main render target.
 */
extern SDL_Window* window;

extern unsigned int VBO;
extern unsigned int VAO;
extern Shader* s;

// camera
extern glm::vec3 cameraPos;
extern glm::vec3 cameraFront;
extern glm::vec3 cameraUp;

// mouse
extern bool firstMouse;
extern float lastX;
extern float lastY;
extern float yaw;
extern float pitch;

// time tracking
extern float deltaTime;
extern float lastFrame;

/**
 * Initializes SDL and OpenGL.
 */
void Init();

/**
 * Draws a frame to the renderer.
 */
void DrawFrame();

/**
 * Frees all memory associated with the renderer.
 */
void Destroy();

/**
 * Reads a text file into a buffer.
 */
void ReadFileToBuffer(const char* filename, char** buffer);

/**
 * Handles mouse input each frame.
 */
void HandleMouseInput(double xOffset, double yOffset);
}  // namespace renderer

#endif
