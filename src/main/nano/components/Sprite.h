#ifndef SPRITE_H
#define SPRITE_H

#define GLEW_STATIC
#define NO_SDL_GLEXT
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include "Position.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../Utility.h"

typedef unsigned int Shader;
typedef unsigned int Texture;

typedef struct Sprite {
  Shader shader;
  Texture texture;
  float* vertices;
  unsigned int* indices;
  unsigned int vao, vbo, ebo;
} Sprite;

typedef struct SPRITEDATA {
  char* vertexfile;
  char* fragmentfile;
  char* texturefile;
  Position* position;
  int width, height;
} SPRITEDATA;

Shader createshader(char* vertexfile, char* fragmentfile) {
  const char* vertexcode = loadshader(vertexfile);
  unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vertexcode, NULL);
  glCompileShader(vertex);

  const char* fragmentcode = loadshader(fragmentfile);
  unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fragmentcode, NULL);
  glCompileShader(fragment);

  Shader shader = glCreateProgram();
  glAttachShader(shader, vertex);
  glAttachShader(shader, fragment);
  glLinkProgram(shader);

  glDeleteShader(vertex);
  glDeleteShader(fragment);
  free((void*) vertexcode);
  free((void*) fragmentcode);

  return shader;
}

Texture createtexture(char* texturefile) {
  Texture texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int width, height, channels;
  unsigned char* texturedata = stbi_load(texturefile, &width, &height, &channels, 0);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texturedata);
  glGenerateMipmap(GL_TEXTURE_2D);
  stbi_image_free(texturedata);

  return texture;
}

Sprite* spritecomponent(SPRITEDATA* data) {
  float vertices[] = {
     (1.0f / 20),  ((float) (data -> width / data -> height) / 20), 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
     (1.0f / 20), -((float) (data -> width / data -> height) / 20), 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
    -(1.0f / 20), -((float) (data -> width / data -> height) / 20), 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
    -(1.0f / 20),  ((float) (data -> width / data -> height) / 20), 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f
  };

  unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
  };

  Sprite* sprite = (Sprite*) malloc(sizeof(Sprite));
  sprite -> texture = createtexture(data -> texturefile);
  sprite -> shader = createshader(data -> vertexfile, data -> fragmentfile);
  sprite -> vertices = (float*) malloc(sizeof(float) * 24);
  memcpy(sprite -> vertices, vertices, sizeof(sprite -> vertices));
  sprite -> indices = (unsigned int*) malloc(sizeof(unsigned int) * 6);
  memcpy(sprite -> indices, indices, sizeof(sprite -> indices));

  glGenVertexArrays(1, &(sprite -> vao));
  glGenBuffers(1, &(sprite -> vbo));
  glGenBuffers(1, &(sprite -> ebo));

  glBindVertexArray(sprite -> vao);
  glBindBuffer(GL_ARRAY_BUFFER, sprite -> vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(sprite -> vertices), sprite -> vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sprite -> ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(sprite -> indices), sprite -> indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (6 * sizeof(float)));
  glEnableVertexAttribArray(2);
  return sprite;
}

Sprite* getsprite(Component* component) {
  if (!(component && ((component -> ID) == SPRITE)))
    return NULL;

  Sprite* sprite = (Sprite*) malloc(sizeof(Sprite));
  memcpy(sprite, component -> component, sizeof(component -> component));
  return sprite;
}

#endif
