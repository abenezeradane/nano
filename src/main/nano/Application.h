#ifndef APPLICATION_H
#define APPLICATION_H

#define GLEW_STATIC
#define NO_SDL_GLEXT
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "Math.h"
#include "Utility.h"

typedef enum bool {false, true} bool;
typedef enum ShaderAttribute {vertexPosition, vertexColor} ShaderAttribute;

typedef struct Color {
  GLfloat rgba[4];
} Color;

typedef struct Renderer {
  unsigned int vao, vbo, ebo;
  unsigned int vs, fs, program;
  const char* vertex;
  const char* fragment;
  char* attributes[2];
  float* projection;
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

static float vertices[] = {
     0.0625f,  0.0625f, 0.0f,
     0.0625f, -0.0625f, 0.0f,
    -0.0625f, -0.0625f, 0.0f,
    -0.0625f,  0.0625f, 0.0f
};

static unsigned int indices[] = {
  0, 1, 3,
  1, 2, 3
};

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
    glShaderSource(app -> renderer -> vs, 1, &(app -> renderer -> vertex), NULL);
    glCompileShader(app -> renderer -> vs);

    app -> renderer -> fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(app -> renderer -> fs, 1, &(app -> renderer -> fragment), NULL);
    glCompileShader(app -> renderer -> fs);

    app -> renderer -> program = glCreateProgram();
    glAttachShader(app -> renderer -> program, app -> renderer -> vs);
    glAttachShader(app -> renderer -> program, app -> renderer -> fs);
    glLinkProgram(app -> renderer -> program);
    glDeleteShader(app -> renderer -> vs);
    glDeleteShader(app -> renderer -> fs);

    glGenVertexArrays(1, &(app -> renderer -> vao));
    glGenBuffers(1, &(app -> renderer -> vbo));
    glGenBuffers(1, &(app -> renderer -> ebo));
    glBindVertexArray(app -> renderer -> vao);

    float test[] = {
       (1.0f / 20),  ((float) (app -> width / app -> height) / 20), 0.0f,
       (1.0f / 20), -((float) (app -> width / app -> height) / 20), 0.0f,
      -(1.0f / 20), -((float) (app -> width / app -> height) / 20), 0.0f,
      -(1.0f / 20),  ((float) (app -> width / app -> height) / 20), 0.0f
    };

    glBindBuffer(GL_ARRAY_BUFFER, app -> renderer -> vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(test), test, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, app -> renderer -> ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    const float* projection = morthographic(0.0f, app -> width, app -> height, 0.0f, 0.0f, 100.0f);
    glUniformMatrix4fv(glGetUniformLocation(app -> renderer -> program, "Projection Matrix"), 1, GL_FALSE, projection);
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
  glUseProgram(app -> renderer -> program);
  glBindVertexArray(app -> renderer -> vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  SDL_GL_SwapWindow(app -> window);
  SDL_Delay(1);
}

void resize(Application* app) {

}

void quit(Application* app) {
  app -> quit = true;
}

void close(Application* app) {
  glDeleteVertexArrays(1, &(app -> renderer -> vao));
  glDeleteBuffers(1, &(app -> renderer -> vbo));
  glDeleteBuffers(1, &(app -> renderer -> ebo));
  glDeleteProgram(app -> renderer -> program);

  SDL_GL_DeleteContext(app -> context);
  SDL_DestroyWindow(app -> window);
  SDL_Quit();
}

#endif
