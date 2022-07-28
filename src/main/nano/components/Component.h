#ifndef COMPONENT_H
#define COMPONENT_H

#include "../Atlas.h"

typedef enum ComponentType {
  POSITION, HEALTH,
  VELOCITY, SPRITE
} ComponentType;

typedef struct Component {
  void* component;
  ComponentType ID;
} Component;

ComponentType getcomponenttype(Component* component) {
  return component -> ID;
}

#endif
