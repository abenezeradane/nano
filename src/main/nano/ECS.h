#ifndef ECS_H
#define ECS_H

#include "Atlas.h"
#include "Miscellaneous.h"

#define NULL_ENTITY MAX_ENTITIES

typedef struct ENTITYMANAGER {
  Entity* living;
  unsigned int count;
} ENTITYMANAGER;

typedef struct COMPONENTMANAGER {
  unsigned int* count;
  Component available[MAX_ENTITIES][MAX_COMPONENTS];
} COMPONENTMANAGER;

typedef struct ECS {
  ENTITYMANAGER* entities;
  COMPONENTMANAGER* components;
} ECS;

static ENTITYMANAGER* createEntityManager(void) {
  ENTITYMANAGER* entities = (ENTITYMANAGER*) malloc(sizeof(ENTITYMANAGER));
  entities -> living = (Entity*) calloc(MAX_ENTITIES, sizeof(Entity));
  entities -> count = 0;
  return entities;
}

static COMPONENTMANAGER* createComponentManager(void) {
  COMPONENTMANAGER* components = (COMPONENTMANAGER*) malloc(sizeof(COMPONENTMANAGER));
  for (Entity entity = 0; entity < MAX_ENTITIES; entity++) {
    for (int Component = 0; Component < MAX_COMPONENTS; Component++)
      (components -> available)[entity][Component] = NULL;
  }

  components -> count = (int*) calloc(MAX_ENTITIES, sizeof(int));
  return components;
}

ECS* createECS(void) {
  ECS* ecs = (ECS*) malloc(sizeof(ECS));
  ecs -> entities = createEntityManager();
  ecs -> components = createComponentManager();
  return ecs;
}

Entity createEntity(ECS* ecs) {
  if (!(ecs && (ecs -> entities -> count < MAX_ENTITIES)))
    return NULL_ENTITY;

  for (Entity available = 0; available < MAX_ENTITIES; available++) {
    if ((ecs -> entities -> living)[available] == 0) {
      (ecs -> entities -> living)[available] = 1;
    	(ecs -> entities -> count)++;
      return available;
    }
  }

  return NULL_ENTITY;
}

Boolean isLiving(ECS* ecs, Entity entity) {
  if (!(ecs && (ecs -> entities -> count < MAX_ENTITIES)))
    return -1;

  if ((ecs -> entities -> living)[entity] == 1)
    return true;
  else
    return false;
}

void destroyEntity(ECS* ecs, Entity entity) {
  if (!(ecs && (ecs -> entities -> count < MAX_ENTITIES)))
    return;

	(ecs -> entities -> living)[entity] = 0;
	(ecs -> entities -> count)--;
}

void createComponent(ECS* ecs, Entity entity, ComponentID type, void* data,...) {
  if (!(ecs && (ecs -> components) && (type < MAX_COMPONENTS)))
    return;

  va_list additionalData;
  va_start(additionalData, data);
  switch (type) {
    case CAMERA:
      (ecs -> components -> available)[entity][type] = cameraComponent((float*) data);
      break;

    case GRAVITY:
      (ecs -> components -> available)[entity][type] = gravityComponent((float*) data);
      break;

    case RIGIDBODY:
      (ecs -> components -> available)[entity][type] = rigidbodyComponent((float*) data, (float*) va_arg(additionalData, void*));
      break;

    case TRANSFORM:
      (ecs -> components -> available)[entity][type] = transformComponent((float*) data, (float*) va_arg(additionalData, void*), (float*) va_arg(additionalData, void*));
      break;

    case SHADER:
      (ecs -> components -> available)[entity][type] = shaderComponent((char*) data, (char*) va_arg(additionalData, void*));
      break;

    case TEXTURE:
      (ecs -> components -> available)[entity][type] = textureComponent((char*) data);
      break;
  }
  va_end(additionalData);

  if (!((ecs -> components -> available)[entity][type]))
    return;

  (ecs -> components -> count)[entity]++;
}

void* getComponent(ECS* ecs, Entity entity, ComponentID type) {
  if (!(ecs && (ecs -> components) && (type < MAX_COMPONENTS)))
    return NULL;

  return (ecs -> components -> available)[entity][type];
}

#endif
