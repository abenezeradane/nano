#ifndef GRAVITY_H
#define GRAVITY_H

#define GRAVITATION_FORCE -0.5f

typedef struct Gravity {
  float force[2];
} Gravity;

Gravity* gravityComponent(float force[2]) {
  Gravity* gravity = (Gravity*) malloc(sizeof(Gravity));

  if (force) {
    (gravity -> force)[0] = force[0];
    (gravity -> force)[1] = force[1];
  } else {
    (gravity -> force)[0] = 0.0f;
    (gravity -> force)[1] = GRAVITATION_FORCE;
  }

  return gravity;
}

#endif
