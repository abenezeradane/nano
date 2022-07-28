#ifndef APPLICATION_H
#define APPLICATION_H

#define GLEW_STATIC
#define NO_SDL_GLEXT
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "ECS.h"
#include "Math.h"
#include "Renderer.h"

typedef struct Application {
  bool vsync, quit, fullscreen;
  const char* title;
  SDL_Window* window;
  SDL_GLContext context;
  Renderer* renderer;
  ECS* ecs;
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
    glGenVertexArrays(1, &(app -> renderer -> vao));
    glGenBuffers(1, &(app -> renderer -> vbo));
    glGenBuffers(1, &(app -> renderer -> ebo));

    glBindVertexArray(app -> renderer -> vao);

    glBindBuffer(GL_ARRAY_BUFFER, app -> renderer -> vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, app -> renderer -> ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (6 * sizeof(float)));
    // glEnableVertexAttribArray(2);
  } else
    exit(-1);

  if (app && app -> load)
    app -> load();
}

void resize(Application* app) {

}

void render(Application* app) {
  for (int entity = 0; entity < ((app -> ecs -> entities).livingcount); entity++) {
    Component component = getcomponent(app -> ecs, entity, SPRITE);
    Sprite* sprite = getsprite(&component);
    if (sprite == NULL)
      continue;

    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glUseProgram(sprite -> shader);
    glBindVertexArray(app -> renderer -> vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }

  SDL_GL_SwapWindow(app -> window);
  SDL_Delay(1);
}

void quit(Application* app) {
  app -> quit = true;
}

void shutdown(Application* app) {
  glDeleteVertexArrays(1, &(app -> renderer -> vao));
  glDeleteBuffers(1, &(app -> renderer -> vbo));
  // for (int entity = 0; entity < ((app -> ecs -> entities).livingcount); entity++) {
  //   Sprite* sprite = getcomponent(app -> ecs, entity, SPRITE).component;
  //   if (sprite == NULL)
  //     continue;
  //   glDeleteProgram(sprite -> shader);
  // }

  SDL_GL_DeleteContext(app -> context);
  SDL_DestroyWindow(app -> window);
  SDL_Quit();
}

#endif
