#ifndef APPLICATION_H
#define APPLICATION_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "util/Filereader.h"

typedef enum {false, true} bool;

typedef struct Color {
  GLfloat rgba[4];
} Color;

typedef struct Renderer {
  GLuint vao, vbo;
  GLuint vs, fs, program;
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
  glViewport(0, 0, app -> width ? app -> width : 800, app -> height ? app -> height : 600);

  if (app && app -> load)
    app -> load();
}

void clear(Color* color) {
  if (color)
    glClearColor((color -> rgba)[0], (color -> rgba)[1], (color -> rgba)[2], (color -> rgba)[3]);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void render(Application* app) {
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
