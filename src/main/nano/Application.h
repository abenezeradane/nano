#ifndef APPLICATION_H
#define APPLICATION_H

#define GLEW_STATIC
#define NO_SDL_GLEXT
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "util/Queue.h"

typedef enum bool {false, true} bool;
typedef enum ShaderAttribute {vertexPosition, vertexColor} ShaderAttribute;

typedef struct Color {
  GLfloat rgba[4];
} Color;

typedef struct Renderer {
  GLuint vao, vbo;
  GLuint vs, fs, program;
  const char* vertex;
  const char* fragment;
  char* attributes[2];
} Renderer;

typedef struct Application {
  bool vsync, quit, fullscreen;
  const char* title;
  SDL_Window* window;
  SDL_GLContext context;
  Renderer* renderer;
  int x, y, width, height, fps, flags;
  void (*step)(void);
  void (*load)(void);
} Application;

double time(void) {
  return (double) SDL_GetTicks();
}

void start(Application* app) {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  app -> window = SDL_CreateWindow(
    app -> title ? app -> title : "Application",
    app -> x ? app -> x : SDL_WINDOWPOS_CENTERED,
    app -> y ? app -> y : SDL_WINDOWPOS_CENTERED,
    app -> width ? app -> width : 800,
    app -> height ? app -> height : 600,
    app -> flags ? app -> flags : SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
  );

  app -> context = SDL_GL_CreateContext(app -> window);
  SDL_GL_SetSwapInterval(app -> vsync ? app -> vsync : false);

  glewInit();
  glDisable(GL_DEPTH_TEST);
  glViewport(0, 0, app -> width ? app -> width : 800, app -> height ? app -> height : 600);

  if (app && app -> renderer) {
    app -> renderer -> vs = glCreateShader(GL_VERTEX_SHADER);
    app -> renderer -> fs = glCreateShader(GL_FRAGMENT_SHADER);

    int len = strlen(app -> renderer -> vertex);
    glShaderSource(app -> renderer -> vs, 1, (const GLchar**) &(app -> renderer -> vertex), &len);
    glCompileShader(app -> renderer -> vs);

    len = strlen(app -> renderer -> fragment);
    glShaderSource(app -> renderer -> fs, 1, (const GLchar**) &(app -> renderer -> fragment), &len);
    glCompileShader(app -> renderer -> fs);

    app -> renderer -> program = glCreateProgram();
    glAttachShader(app -> renderer -> program, app -> renderer -> vs);
    glAttachShader(app -> renderer -> program, app -> renderer -> fs);

    glBindAttribLocation(app -> renderer -> program, vertexPosition, app -> renderer -> attributes[0] ? app -> renderer -> attributes[0] : "POSITION");
    glBindAttribLocation(app -> renderer -> program, vertexColor, app -> renderer -> attributes[1] ? app -> renderer -> attributes[1] : "COLOR");
    glLinkProgram(app -> renderer -> program);
    glUseProgram(app -> renderer -> program);

    glGenVertexArrays(1, &(app -> renderer -> vao));
    glGenBuffers(1, &(app -> renderer -> vbo));
    glBindVertexArray(app -> renderer -> vao);
    glBindBuffer( GL_ARRAY_BUFFER, app -> renderer -> vbo);

    glEnableVertexAttribArray(vertexColor);
    glEnableVertexAttribArray(vertexPosition);
    glVertexAttribPointer(vertexColor, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
    glVertexAttribPointer(vertexPosition, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*) (4 * sizeof(float)));
  }

  if (app && app -> load)
    app -> load();
}

void clear(Color* color) {
  if (color)
    glClearColor((color -> rgba)[0], (color -> rgba)[1], (color -> rgba)[2], (color -> rgba)[3]);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void render(Application* app) {
  glBindVertexArray(app -> renderer -> vao);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  SDL_GL_SwapWindow(app -> window);
}

void resize(Application* app) {

}

void quit(Application* app) {
  app -> quit = true;
}

void close(Application* app) {
  SDL_GL_DeleteContext(app -> context);
  SDL_DestroyWindow(app -> window);
  SDL_Quit();
}

#endif
