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

float* morthographic(float l, float r, float b, float t, float n, float f) {
  float grid[16];
  for (int itr = 0; itr < 16; itr++)
      grid[itr] = 0.0f;

  grid[0] = 2.0f / (r - l);
  grid[4] = 2.0f / (t - b);
  grid[9] = -2.0f / (f - n);
  grid[11] = -(r + l) / (r - l);
  grid[12] = -(t + b) / (t - b);
  grid[13] = -(f + n) / (f - n);
  grid[14] = -1.0f;
}

#endif
