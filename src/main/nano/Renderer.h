#ifndef SHADER_H
#define SHADER_H

#define GLEW_STATIC
#define NO_SDL_GLEXT
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include "Utility.h"

typedef enum bool {false, true} bool;
typedef unsigned int Shader;
typedef struct Renderer {
  unsigned int vao, vbo, ebo;
  unsigned short count;
  Shader shaders[512];
  float* projection;
} Renderer;

unsigned int indices[] = {
  0, 1, 3,
  1, 2, 3
};

void createshader(Renderer* renderer, char* vertexfile, char* fragmentfile) {
  const char* vertexcode = loadshader(vertexfile);
  unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vertexcode, NULL);
  glCompileShader(vertex);

  const char* fragmentcode = loadshader(fragmentfile);
  unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fragmentcode, NULL);
  glCompileShader(fragment);

  unsigned int SHADERID = glCreateProgram();
  glAttachShader(SHADERID, vertex);
  glAttachShader(SHADERID, fragment);
  glLinkProgram(SHADERID);

  (renderer -> shaders)[(renderer -> count)++] = SHADERID;

  glDeleteShader(vertex);
  glDeleteShader(fragment);
  free((void*) vertexcode);
  free((void*) fragmentcode);
}

void setshaderbool(Shader shader, char* attribute, bool value) {
   glUniform1i(glGetUniformLocation(shader, attribute), value);
}

void setshaderint(Shader shader, char* attribute, int value) {
   glUniform1i(glGetUniformLocation(shader, attribute), value);
}

void setshaderfloat(Shader shader, char* attribute, float value) {
   glUniform1i(glGetUniformLocation(shader, attribute), value);
}

#endif
