#ifndef APPLICATION_H
#define APPLICATION_H

#include <SDL2/SDL.h>

typedef enum {false, true} bool;

typedef struct Application {
  bool quit;
  const char* title;
  SDL_Window* window;
  int x, y, width, height, fps;
  void (*load)(void);
} Application;

void start(Application* app) {
  SDL_Init(SDL_INIT_VIDEO);
  app -> window = SDL_CreateWindow(
    app -> title ? app -> title : "Application",
    app -> x ? app -> x : SDL_WINDOWPOS_CENTERED,
    app -> y ? app -> y : SDL_WINDOWPOS_CENTERED,
    app -> width ? app -> width : 800,
    app -> height ? app -> height : 600,
    SDL_WINDOW_SHOWN
  );

  if (app && app -> load)
    app -> load();
}

double time(void) {
  return (double) SDL_GetTicks();
}

#endif
