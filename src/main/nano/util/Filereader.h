#ifndef UTILITY_H
#define UTILITY_H

#define BUFFSIZE 1024
#define MAXSIZE 1048576

char* readfile(const char* filename) {
  FILE* file = fopen(filename, "rb");
  if(!file)
    exit(-1);

  int flag = 0;
  char* shader = (char*) malloc(MAXSIZE);

  char* buffer = (char*) malloc(BUFFSIZE);
  while (fgets(buffer, BUFFSIZE, file) != NULL) {
    if (flag++ == 0)
      memcpy(shader, buffer, BUFFSIZE);
    else
      strcat(shader, buffer);
  }

  free(buffer);
  fclose(file);
  if (strlen(shader) != MAXSIZE) {
    char* temp = (char*) malloc(strlen(shader));
    memcpy(temp, shader, strlen(shader));
    free(shader);
    return temp;
  }

  return shader;
}

#endif
