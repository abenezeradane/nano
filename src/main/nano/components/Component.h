#ifndef COMPONENT_H
#define COMPONENT_H

typedef enum ComponentID {
  NULL_COMPONENT,
  CAMERA,
  GRAVITY, RIGIDBODY, TRANSFORM,
  SHADER, TEXTURE,
  NUM_OF_COMPONENTIDS
} ComponentID;

typedef void* Component;

#endif
