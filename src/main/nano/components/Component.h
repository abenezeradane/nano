#ifndef COMPONENT_H
#define COMPONENT_H

typedef enum ComponentID {
  CAMERA,
  GRAVITY, RIGIDBODY, TRANSFORM,
  SHADER, TEXTURE
} ComponentID;

typedef void* Component;

#endif
