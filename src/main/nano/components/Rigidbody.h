#ifndef RIGIDBODY_H
#define RIGIDBODY_H

typedef struct Rigidbody {
  float velocity[2];
  float acceleration[2];
} Rigidbody;

Rigidbody* rigidbodyComponent(float velocity[2], float acceleration[2]) {
  Rigidbody* rigidbody = (Rigidbody*) malloc(sizeof(Rigidbody));

  if (velocity) {
    (rigidbody -> velocity)[0] = velocity[0];
    (rigidbody -> velocity)[1] = velocity[1];
  } else {
    (rigidbody -> velocity)[0] = 0.0f;
    (rigidbody -> velocity)[1] = 0.0f;
  }

  if (acceleration) {
    (rigidbody -> acceleration)[0] = acceleration[0];
    (rigidbody -> acceleration)[1] = acceleration[1];
  } else {
    (rigidbody -> acceleration)[0] = 0.0f;
    (rigidbody -> acceleration)[1] = 0.0f;
  }

  return rigidbody;
}

#endif
