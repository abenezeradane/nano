#ifndef SPRITE_H
#define SPRITE_H

#include "../Atlas.h"

typedef unsigned int Shader;
typedef unsigned int Texture;

typedef struct Sprite {
  Shader shader;
  Texture texture;
} Sprite;

#endif
