#ifndef RENDERER_H
#define RENDERER_H

#define GLEW_STATIC
#define NO_SDL_GLEXT
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include "ECS.h"

typedef struct Color {
  GLfloat rgba[4];
} Color;

typedef struct Renderer {
  float* projection;
} Renderer;

void clear(Color* color) {
  if (color)
    glClearColor((color -> rgba)[0], (color -> rgba)[1], (color -> rgba)[2], (color -> rgba)[3]);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// void createshader(Renderer* renderer, char* vertexfile, char* fragmentfile) {
//   const char* vertexcode = loadshader(vertexfile);
//   unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
//   glShaderSource(vertex, 1, &vertexcode, NULL);
//   glCompileShader(vertex);
//
//   const char* fragmentcode = loadshader(fragmentfile);
//   unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
//   glShaderSource(fragment, 1, &fragmentcode, NULL);
//   glCompileShader(fragment);
//
//   Shader shader = glCreateProgram();
//   glAttachShader(shader, vertex);
//   glAttachShader(shader, fragment);
//   glLinkProgram(shader);
//
//   glDeleteShader(vertex);
//   glDeleteShader(fragment);
//   free((void*) vertexcode);
//   free((void*) fragmentcode);
//
//   (renderer -> shaders)[(renderer -> shadercount)++] = shader;
// }

#endif
