#ifndef APPLICATION_H
#define APPLICATION_H

#define GLEW_STATIC
#define NO_SDL_GLEXT
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "Miscellaneous.h"

#include "ECS.h"

typedef struct Application {
  const char* title;
  SDL_Window* window;
  SDL_GLContext context;

  Boolean vsync, quit, fullscreen;
  int x, y, width, height, fps, flags;

  ECS* ecs;

  void (*step)(void);
  void (*load)(void);
} Application;

double time(void) {
  return (double) SDL_GetTicks();
}

void start(Application* app) {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE) != 0) {
    char msg[1024];
    error(strcat(strcpy(msg, "SDL2 Failed to Initialize!\n> SDL2 Error: "), SDL_GetError()));
  }

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
    app -> title ? app -> title : "Nano Engine",
    app -> x ? app -> x : SDL_WINDOWPOS_CENTERED,
    app -> y ? app -> y : SDL_WINDOWPOS_CENTERED,
    app -> width ? app -> width : 800,
    app -> height ? app -> height : 600,
    app -> flags ? app -> flags : SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
  );

  if ((app -> window) == NULL) {
    char msg[1024];
    error(strcat(strcpy(msg, "SDL2 Failed to Create Window!\n> SDL2 Error: "), SDL_GetError()));
  }

  app -> context = SDL_GL_CreateContext(app -> window);
  if (!(app -> context)) {
    char msg[1024];
    error(strcat(strcpy(msg, "SDL2 Failed to Create OpenGL Context!\n> SDL2 Error: "), SDL_GetError()));
  }

  glewInit();
  glEnable(GL_BLEND);
  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);
  app -> ecs = createECS();
  if (app -> load)
    app -> load();
}

void clear(float color[4]) {
  if (color)
    glClearColor(color[0], color[1], color[2], color[3]);
}

void draw(Application* app) {
  SDL_GL_SwapWindow(app -> window);
  SDL_Delay(1);
}

void close(Application* app) {
  SDL_DestroyWindow(app -> window);
  SDL_Quit();
}

#endif
