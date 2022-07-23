#ifndef MATRIX_H
#define MATRIX_H

#include <math.h>

typedef struct Matrix {
  short row, column;
  float grid[4][4];
} Matrix;

void madd(Matrix* a, Matrix* b) {
  if (((a -> row) == (b -> row)) && ((a -> column) == (b -> column))) {
    for (int itr = 0; itr < (a -> row); itr++) {
      for(int ir = 0; ir < (a -> column); ir++)
        (a -> grid)[itr][ir] += (b -> grid)[itr][ir];
    }
  }
}

void msub(Matrix* a, Matrix* b) {
  if (((a -> row) == (b -> row)) && ((a -> column) == (b -> column))) {
    for (int itr = 0; itr < (a -> row); itr++) {
      for(int ir = 0; ir < (a -> column); ir++)
        (a -> grid)[itr][ir] -= (b -> grid)[itr][ir];
    }
  }
}

void mmult(Matrix* a, float b) {
  for (int itr = 0; itr < (a -> row); itr++) {
    for(int ir = 0; ir < (a -> column); ir++)
      (a -> grid)[itr][ir] *= b;
  }
}

void mdiv(Matrix* a, float b) {
  for (int itr = 0; itr < (a -> row); itr++) {
    for(int ir = 0; ir < (a -> column); ir++)
      (a -> grid)[itr][ir] /= b;
  }
}

#endif
