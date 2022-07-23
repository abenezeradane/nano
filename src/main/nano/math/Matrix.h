#ifndef MATRIX_H
#define MATRIX_H

#include <math.h>

typedef struct Matrix {
  short size;
  Vector grid[4];
} Matrix;

void madd(Matrix* a, Matrix* b) {
  if ((a -> size) == (b -> size)) {
    for (int itr = 0; itr < (a -> size); itr++) {
      for(int ir = 0; ir < (a -> size); ir++)
        (a -> grid)[itr].array[ir] += (b -> grid)[itr].array[ir];
    }
  }
}

void msub(Matrix* a, Matrix* b) {
  if ((a -> size) == (b -> size)) {
    for (int itr = 0; itr < (a -> size); itr++) {
      for(int ir = 0; ir < (a -> size); ir++)
        (a -> grid)[itr].array[ir] -= (b -> grid)[itr].array[ir];
    }
  }
}

void mmult(Matrix* a, float b) {
  for (int itr = 0; itr < (a -> size); itr++) {
    for(int ir = 0; ir < (a -> size); ir++)
      (a -> grid)[itr].array[ir] *= b;
  }
}

void mdiv(Matrix* a, float b) {
  for (int itr = 0; itr < (a -> size); itr++) {
    for(int ir = 0; ir < (a -> size); ir++)
      (a -> grid)[itr].array[ir] /= b;
  }
}

#endif
