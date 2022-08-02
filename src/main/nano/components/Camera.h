#ifndef CAMERA_H
#define CAMERA_H

typedef struct Camera {
  float projection[16];
} Camera;

Camera* cameraComponent(float projection[16]) {
  Camera* camera = (Camera*) malloc(sizeof(Camera));

  if (projection) {
    for (int i = 0; i < 16; i++)
      (camera -> projection)[i] = projection[i];
  } else {
    for (int i = 0; i < 16; i++)
      (camera -> projection)[i] = 1.0f;
  }

  return camera;
}

#endif
