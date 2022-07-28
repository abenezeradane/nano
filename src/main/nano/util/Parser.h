#ifndef PARSER_H
#define PARSER_H

#define BUFFSIZE 1024
#define MAXSIZE 1048576

char* loadshader(const char* filename) {
  FILE* file = fopen(filename, "r");
  if(file == NULL)
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

char* loadtexture(const char* filename) {
  return NULL;
}

#endif
