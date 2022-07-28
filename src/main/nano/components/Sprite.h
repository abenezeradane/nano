#ifndef SPRITE_H
#define SPRITE_H

#define GLEW_STATIC
#define NO_SDL_GLEXT
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include "../Atlas.h"
#include "../Utility.h"

typedef unsigned int Shader;
typedef unsigned int Texture;

typedef struct Sprite {
  Shader shader;
  Texture texture;
} Sprite;

typedef struct SPRITEDATA {
  char* vertexfile;
  char* fragmentfile;
  char* texturefile;
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

Sprite* spritecomponent(SPRITEDATA* data) {
  Sprite* sprite = (Sprite*) malloc(sizeof(Sprite));
  sprite -> shader = createshader(data -> vertexfile, data -> fragmentfile);
  return sprite;
}

Sprite* getsprite(Component* component) {
  if (!(component && ((component -> ID) == POSITION)))
    return NULL;

  Sprite* sprite = (Sprite*) malloc(sizeof(Sprite));
  memcpy(sprite, component -> component, sizeof(component -> component));
  return sprite;
}

#endif
