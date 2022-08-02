#ifndef SHADER_H
#define SHADER_H

#define GLEW_STATIC
#define NO_SDL_GLEXT
#include <GL/glew.h>
#include "../Miscellaneous.h"

typedef struct Shader {
  Boolean generated;
  unsigned int data;
  unsigned int VBO, VAO, EBO;
} Shader;


unsigned int createShader(char* vertexfile, char* fragmentfile) {
  const char* vertexcode = loadshader(vertexfile);
  unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vertexcode, NULL);
  glCompileShader(vertex);

  {
    char log[1024]; int success; glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(vertex, 1024, NULL, log);
      error(strcat("Vertex Shader Failed to Compile!\n> OpenGL Error: %s\n", log));
    }
  }

  const char* fragmentcode = loadshader(fragmentfile);
  unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fragmentcode, NULL);
  glCompileShader(fragment);

  {
    char log[1024]; int success; glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(fragment, 1024, NULL, log);
      error(strcat("Fragment Shader Failed to Compile!\n> OpenGL Error: %s\n", log));
    }
  }

  unsigned int data = glCreateProgram();
  glAttachShader(data, vertex);
  glAttachShader(data, fragment);
  glLinkProgram(data);

  {
    char log[1024]; int success; glGetProgramiv(data, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(data, 1024, NULL, log);
      error(strcat("Shader Failed to Link!\n> OpenGL Error: %s", log));
    }
  }

  glDeleteShader(vertex);
  glDeleteShader(fragment);
  free((void*) vertexcode);
  free((void*) fragmentcode);

  return data;
}

Shader* shaderComponent(char* vertexfile, char* fragmentfile) {
  Shader* shader = (Shader*) malloc(sizeof(Shader));
  shader -> data = createShader(vertexfile, fragmentfile);
  shader -> generated = false;
  return shader;
}

#endif
