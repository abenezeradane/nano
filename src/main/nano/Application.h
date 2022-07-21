#ifndef APPLICATION_H
#define APPLICATION_H

#include <SDL2/SDL.h>

typedef enum {false, true} bool;

typedef struct Application {
  SDL_Window* window;
  const char* title;
  int x, y, width, height;
  bool quit;
  void (*step)(void);
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

#endif
