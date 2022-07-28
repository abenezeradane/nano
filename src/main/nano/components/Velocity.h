#ifndef VELOCITY_H
#define VELOCITY_H

#include "../Atlas.h"
#include "../Math.h"

typedef struct Velocity {
  Vector vector;
} Velocity;

Velocity* velocitycomponent(void) {
  Velocity* velocity = (Velocity*) malloc(sizeof(Velocity));
  velocity -> vector = vector(2);

  return velocity;
}

#endif
