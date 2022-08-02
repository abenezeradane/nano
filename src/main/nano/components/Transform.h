#ifndef TRANSFORM_H
#define TRANSFORM_H

typedef struct Transform {
  float position[2];
  float rotation[2];
  float scale[2];
} Transform;

Transform* transformComponent(float position[2], float rotation[2], float scale[2]) {
  Transform* transform = (Transform*) malloc(sizeof(Transform));

  if (position) {
    (transform -> position)[0] = position[0];
    (transform -> position)[1] = position[1];
  } else {
    (transform -> position)[0] = 0.0f;
    (transform -> position)[1] = 0.0f;
  }

  if (rotation) {
    (transform -> rotation)[0] = rotation[0];
    (transform -> rotation)[1] = rotation[1];
  } else {
    (transform -> rotation)[0] = 0.0f;
    (transform -> rotation)[1] = 0.0f;
  }

  if (scale) {
    (transform -> scale)[0] = scale[0];
    (transform -> scale)[1] = scale[1];
  } else {
    (transform -> scale)[0] = 1.0f;
    (transform -> scale)[1] = 1.0f;
  }

  return transform;
}

#endif
