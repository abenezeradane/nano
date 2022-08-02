#ifndef PHYSICS_H
#define PHYSICS_H

#include "../ECS.h"

void updatePhysics(ECS* ecs, float delta) {
  if (!ecs)
    return;

  for (Entity entity = 0; entity < (ecs -> entities -> count); entity++) {
    if (isLiving(ecs, entity)) {
      Gravity* gravity = (Gravity*) getComponent(ecs, entity, GRAVITY);
      Rigidbody* rigidbody = (Rigidbody*) getComponent(ecs, entity, RIGIDBODY);
      Transform* transform = (Transform*) getComponent(ecs, entity, TRANSFORM);

      if ((gravity == NULL) || (rigidbody == NULL) || (transform == NULL))
        continue;

      for (int itr = 0; itr < 2; itr++) {
        (gravity -> force)[itr] *= delta;
        (rigidbody -> velocity)[itr] *= delta;

        (transform -> position)[itr] += (gravity -> force)[itr];
        (transform -> position)[itr] += (rigidbody -> velocity)[itr];
      }
    }
  }
}

#endif
