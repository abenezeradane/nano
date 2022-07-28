#ifndef ECS_H
#define ECS_H

#include "Atlas.h"
#include "Utility.h"

typedef struct ENTITYMANAGER {
  Queue* available;
  Entity livingcount;
} ENTITYMANAGER;

typedef struct COMPONENTMANAGER {
  Component** available;
  unsigned short livingcount[MAX_ENTITIES];
} COMPONENTMANAGER;

typedef struct ECS {
  ENTITYMANAGER entities;
  COMPONENTMANAGER components;
  ComponentType typecount[sizeof(ComponentType)];
} ECS;

ENTITYMANAGER entitymanager(void) {
  ENTITYMANAGER manager = {
    .livingcount = 0,
    .available = queue(MAX_ENTITIES)
  };

  empty(manager.available);
  for (int itr = MAX_ENTITIES - 1; itr >= 0; itr--)
    enqueue(manager.available, itr);

  return manager;
}

Entity newentity(ECS* ecs) {
  if (!(ecs && ((ecs -> entities).livingcount < MAX_ENTITIES)))
    return -1;

  Entity ID = front((ecs -> entities).available);
	dequeue((ecs -> entities).available);
	(ecs -> entities).livingcount++;

  return ID;
}

COMPONENTMANAGER componentmanager(void) {
  COMPONENTMANAGER manager = {
    .available = (Component**) malloc(sizeof(Component*) * MAX_ENTITIES),
    .livingcount = 0
  };

  for (int itr = 0; itr < MAX_ENTITIES; itr++)
    (manager.available)[itr] = (Component*) malloc(sizeof(Component) * MAX_COMPONENTS);

  return manager;
}

Component newcomponent(ComponentType type, void* data) {
  Component component = {
    .ID = type,
  };

  switch (type) {
    case POSITION:
      component.component = positioncomponent();
      break;

    case VELOCITY:
      component.component = velocitycomponent();
      break;

    case SPRITE:
      component.component = spritecomponent(data);
      break;

    case HEALTH:
      component.component = (Health*) malloc(sizeof(Health));
      break;
  }

  return component;
}

Component* getcomponents(ECS* ecs, Entity entity) {
  if (!(ecs && (ecs -> entities).livingcount < MAX_ENTITIES))
    return NULL;

  return (ecs -> components).available[entity];
}

Component getcomponent(ECS* ecs, Entity entity, ComponentType type) {
  if (!(ecs && (ecs -> entities).livingcount < MAX_ENTITIES))
    return;

  return (ecs -> components).available[entity][type];
  return;
}

void assigncomponent(ECS* ecs, Component component, Entity entity) {
  if (!(ecs && ((ecs -> components).livingcount[entity] < MAX_COMPONENTS)))
    return;

  (ecs -> components).available[entity][component.ID] = component;
  (ecs -> components).livingcount[entity]++;
  (ecs -> typecount)[component.ID]++;
}

#endif
