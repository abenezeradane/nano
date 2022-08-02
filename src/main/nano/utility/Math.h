#ifndef MATH_H
#define MATH_H

#include <math.h>

void addVector(float* a, float* b) {
  if ((sizeof(a) / sizeof(float)) == (sizeof(b) / sizeof(float))) {
    for (int itr = 0; itr < (sizeof(a) / sizeof(float)); itr++)
      a[itr] += b[itr];
  }
}

void subtractVector(float* a, float* b) {
  if ((sizeof(a) / sizeof(float)) == (sizeof(b) / sizeof(float))) {
    for (int itr = 0; itr < (sizeof(a) / sizeof(float)); itr++)
      a[itr] -= b[itr];
  }
}

void multiplyVector(float* a, float b) {
  for (int itr = 0; itr < (sizeof(a) / sizeof(float)); itr++)
    a[itr] *= b;
}

void divideVector(float* a, float b) {
  for (int itr = 0; itr < (sizeof(a) / sizeof(float)); itr++)
    a[itr] /= b;
}

float vectorMagnitude(float* a) {
  return sqrt(pow(a[0], 2) + pow(a[1], 2) + pow(a[2], 2) + pow(a[3], 2));
}

float* normalizeVector(float* a) {
  float* b = (float*) calloc((sizeof(a) / sizeof(float)), sizeof(float));
  for (int itr = 0; itr < (sizeof(a) / sizeof(float)); itr++)
    b[itr] = a[itr];
  divideVector(b, vectorMagnitude(a));
  return b;
}

float dotProduct(float* a, float* b) {
  return ((a[0] * b[0]) + (a[1] * b[1]) + (a[2] * b[2]) + (a[3] * b[3]));
}

float* crossProduct(float* a, float* b) {
  float* product = (float*) calloc(3, sizeof(float));
  product[0] = (a[1] * b[2]) - (b[1] * a[2]);
  product[1] = (a[0] * b[2]) - (b[0] * a[2]);
  product[2] = (a[0] * b[1]) - (b[0] * a[1]);
  return product;
}

#endif
