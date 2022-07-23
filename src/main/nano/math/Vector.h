#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

typedef struct Vector {
  short size;
  float array[4];
} Vector;

Vector vzero(short size) {
  Vector v = {
    .size = size,
    .array = {0, 0, 0, 0}
  };
  return v;
}

void vadd(Vector* a, Vector* b) {
  if (a -> size == b -> size) {
    for (int itr = 0; itr < (a -> size); itr++)
      (a -> array)[itr] += (b -> array)[itr];
  }
}

void vsub(Vector* a, Vector* b) {
  if (a -> size == b -> size) {
    for (int itr = 0; itr < (a -> size); itr++)
      (a -> array)[itr] -= (b -> array)[itr];
  }
}

void vmult(Vector* a, float b) {
  for (int itr = 0; itr < (a -> size); itr++)
    (a -> array)[itr] *= b;
}

void vdiv(Vector* a, float b) {
  for (int itr = 0; itr < (a -> size); itr++)
    (a -> array)[itr] /= b;
}

float vmagnitude(Vector* a) {
  return sqrt(pow((a -> array)[0], 2) + pow((a -> array)[1], 2) + pow((a -> array)[2], 2) + pow((a -> array)[3], 2));
}

Vector vnormalize(Vector* a) {
  Vector b = *a;
  vdiv(&b, vmagnitude(a));
  return b;
}

float vdot(Vector* a, Vector* b) {
  return (((a -> array)[0] * (b -> array)[0]) + ((a -> array)[1] * (b -> array)[1]) + ((a -> array)[2] * (b -> array)[2]) + ((a -> array)[3] * (b -> array)[3]));
}

Vector vcross(Vector* a, Vector* b) {
  Vector v = {
    .size = 4,
    .array = {
      ((a -> array)[1] * (b -> array)[2]) - ((b -> array)[1] * (a -> array)[2]),
      ((a -> array)[0] * (b -> array)[2]) - ((b -> array)[0] * (a -> array)[2]),
      ((a -> array)[0] * (b -> array)[1]) - ((b -> array)[0] * (a -> array)[1]),
    }
  };
  return v;
}

#endif
