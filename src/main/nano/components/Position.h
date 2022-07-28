#ifndef POSITION_H
#define POSITION_H

#include "../Atlas.h"

typedef struct Position {
  float x, y;
} Position;

Position* positioncomponent(void) {
  Position* position = (Position*) malloc(sizeof(Position));
  position -> x = 0;
  position -> y = 0;

  return position;
}

void setposition(Component* component, float x, float y) {
  if (!(component && ((component -> ID) == POSITION)))
    return;

  Position* position = (Position*) malloc(sizeof(Position));
  position -> x = x;
  position -> y = y;

  component -> component = (Position*) malloc(sizeof(Position));
  memcpy(component -> component, position, sizeof(position));
  free(position);
}

float* getposition(Component* component) {
  if (!(component && ((component -> ID) == POSITION)))
    return NULL;

  float* current = (float*) malloc(sizeof(float) * 2);
  memcpy(current, component -> component, sizeof(component -> component));
  return current;
}

#endif
