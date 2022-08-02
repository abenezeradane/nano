#ifndef MISCELLANEOUS_H
#define MISCELLANEOUS_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

typedef enum Boolean {false = 0, FALSE = 0, TRUE = 1, true = 1} Boolean;

#define BUFFSIZE 1024
#define MAXSIZE 1048576

char* loadshader(char* filename) {
  FILE* file = fopen(filename, "r");
  if (!file)
    return NULL;

  int flag = 0;
  char* shader = (char*) malloc(MAXSIZE);
  char* buffer = (char*) malloc(BUFFSIZE);
  while (fgets(buffer, BUFFSIZE, file) != NULL)
    strcat(shader, buffer);

  free(buffer);
  fclose(file);
  return shader;
}

void error(char* msg) {
  fprintf(stderr, "\x1b[5m\x1B[31mError\x1B[0m: %s\n", msg);
  exit(-1);
}



#endif
