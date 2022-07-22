#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

typedef struct Vector2D {
  float x, y;
} Vector2D;

typedef struct Vector3D {
  float x, y, z;
} Vector3D;

typedef struct Vector4D {
  float x, y, z, w;
} Vector4D;

void vectoradd(void* a, void* b) {
  if (sizeof(a) == sizeof(b)) {
    switch (sizeof(a)) {
      case sizeof(Vector2D):
      {
        Vector2D* m = (Vector2D*) a;
        Vector2D* n = (Vector2D*) b;
        m -> x += n -> x;
        m -> y += n -> y;
        a = m;
        break;
      }

      case sizeof(Vector3D):
      {
        Vector3D* m = (Vector3D*) a;
        Vector3D* n = (Vector3D*) b;
        m -> x += n -> x;
        m -> y += n -> y;
        m -> z += n -> z;
        a = m;
        break;
      }

      case sizeof(Vector4D):
      {
        Vector4D* m = (Vector4D*) a;
        Vector4D* n = (Vector4D*) b;
        m -> x += n -> x;
        m -> y += n -> y;
        m -> z += n -> z;
        m -> w += n -> w;
        a = m;
        break;
      }
    }
  }
}

void vectorsub(void* a, void* b) {
  if (sizeof(a) == sizeof(b)) {
    switch (sizeof(a)) {
      case sizeof(Vector2D):
      {
        Vector2D* m = (Vector2D*) a;
        Vector2D* n = (Vector2D*) b;
        m -> x -= n -> x;
        m -> y -= n -> y;
        a = m;
        break;
      }

      case sizeof(Vector3D):
      {
        Vector3D* m = (Vector3D*) a;
        Vector3D* n = (Vector3D*) b;
        m -> x -= n -> x;
        m -> y -= n -> y;
        m -> z -= n -> z;
        a = m;
        break;
      }

      case sizeof(Vector4D):
      {
        Vector4D* m = (Vector4D*) a;
        Vector4D* n = (Vector4D*) b;
        m -> x -= n -> x;
        m -> y -= n -> y;
        m -> z -= n -> z;
        m -> w -= n -> w;
        a = m;
        break;
      }
    }
  }
}

void vectorscalar(void* a, float b) {
  if (sizeof(a) == sizeof(b)) {
    switch (sizeof(a)) {
      case sizeof(Vector2D):
      {
        Vector2D* m = (Vector2D*) a;
        m -> x *= b;
        m -> y *= b;
        a = m;
        break;
      }

      case sizeof(Vector3D):
      {
        Vector3D* m = (Vector3D*) a;
        m -> x *= b;
        m -> y *= b;
        m -> z *= b;
        a = m;
        break;
      }

      case sizeof(Vector4D):
      {
        Vector4D* m = (Vector4D*) a;
        m -> x *= b;
        m -> y *= b;
        m -> z *= b;
        m -> w *= b;
        a = m;
        break;
      }
    }
  }
}

float vectormagnitude(void* a) {
  switch (sizeof(a)) {
    case sizeof(Vector2D):
    {
      Vector2D* b = (Vector2D*) a;
      return sqrt(pow(b -> x, 2) + pow(b -> y, 2));
    }

    case sizeof(Vector3D):
    {
      Vector3D* b = (Vector3D*) a;
      return sqrt(pow(b -> x, 2) + pow(b -> y, 2) + pow(b -> z, 2));
    }

    case sizeof(Vector4D):
    {
      Vector4D* b = (Vector4D*) a;
      return sqrt(pow(b -> x, 2) + pow(b -> y, 2) + pow(b -> z, 2) + pow(b -> w, 2));
    }
  }

  return -1.0;
}

float vectordot(void* a, void* b) {
  if (sizeof(a) == sizeof(b)) {
    switch (sizeof(a)) {
      case sizeof(Vector2D):
      {
        Vector2D* m = (Vector2D*) a;
        Vector2D* n = (Vector2D*) b;
        return (((m -> x) * (n -> x)) + ((m -> y) * (n -> y)));
      }

      case sizeof(Vector3D):
      {
        Vector3D* m = (Vector3D*) a;
        Vector3D* n = (Vector3D*) b;
        return (((m -> x) * (n -> x)) + ((m -> y) * (n -> y)) + ((m -> z) * (n -> z)));
      }

      case sizeof(Vector4D):
      {
        Vector4D* m = (Vector4D*) a;
        Vector4D* n = (Vector4D*) b;
        return (((m -> x) * (n -> x)) + ((m -> y) * (n -> y)) + ((m -> z) * (n -> z)) + ((m -> w) * (n -> w)));
      }
    }
  }

  return (1.0 / 0.0);
}

Vector3D vectorcross(Vector3D* a, Vector3D* b) {
  Vector3D c = {0};
  c.x = ((a -> y) * (b -> z)) - ((a -> z) * (b -> y));
  c.y = ((a -> z) * (b -> x)) - ((a -> x) * (b -> z));
  c.z = ((a -> y) * (b -> x)) - ((a -> x) * (b -> y));
  return c;
}

#endif
