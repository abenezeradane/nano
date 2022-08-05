#ifndef INPUT_H
#define INPUT_H

#include "Application.h"
#include "Miscellaneous.h"

enum {
  KEY_UNKNOWN,

  KEY_MOUSE_LEFT,
  KEY_MOUSE_RIGHT,
  KEY_MOUSE_MIDDLE,

  KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G,
  KEY_H, KEY_I, KEY_J, KEY_K, KEY_L, KEY_M, KEY_N,
  KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U,
  KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z,

  KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6,
  KEY_7, KEY_8, KEY_9,

  KEY_ESCAPE, KEY_RETURN, KEY_LCTRL, KEY_LALT,
  KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN,
  KEY_LSHIFT, KEY_SPACE,

  KEY_MAX
};

static Boolean KEY_DELTA[KEY_MAX];
static Boolean KEY_PRESSED[KEY_MAX];

Boolean keydown(int key) {
  return KEY_PRESSED[key];
}

Boolean keypress(int key) {
  return KEY_PRESSED[key] && KEY_DELTA[key];
}

Boolean keyrelease(int key) {
  return !KEY_PRESSED[key] && KEY_DELTA[key];
}

static void resetInput(void) {
  memset(KEY_DELTA, 0, sizeof(KEY_DELTA));
}

static void onKeypress(int key) {
  if (key) {
    KEY_PRESSED[key] = true;
    KEY_DELTA[key] = true;
  }
}

static void onKeyrelease(int key) {
  if (key) {
    KEY_PRESSED[key] = false;
    KEY_DELTA[key] = true;
  }
}

int translateKey(int key) {
  if (key >= 0x61 && key <= 0x7A) return key - 0x61 + KEY_A;
  if (key >= 0x30 && key <= 0x39) return key - 0x30 + KEY_A;

  switch (key) {
    case SDLK_LALT: return KEY_LALT;
    case SDLK_ESCAPE: return KEY_ESCAPE;
    case SDLK_LEFT: return KEY_LEFT;
    case SDLK_RIGHT: return KEY_RIGHT;
    case SDLK_UP: return KEY_UP;
    case SDLK_DOWN: return KEY_DOWN;
    case SDLK_LSHIFT: return KEY_LSHIFT;
    case SDLK_SPACE: return KEY_SPACE;
  }

  return 0;
}

static void inputProc(Application* app) {
  SDL_Event event;
  if (SDL_PollEvent(&event) != 0) {
    if (event.type == SDL_QUIT)
      app -> quit = true;

    else if (event.type == SDL_MOUSEBUTTONDOWN) {
      switch (event.button.button) {
        case SDL_BUTTON_LEFT:
          onKeypress(KEY_MOUSE_LEFT);
          break;

        case SDL_BUTTON_MIDDLE:
          onKeypress(KEY_MOUSE_MIDDLE);
          break;

        case SDL_BUTTON_RIGHT:
          onKeypress(KEY_MOUSE_RIGHT);
          break;
      }
    }

    else if (event.type == SDL_MOUSEBUTTONUP) {
      switch (event.button.button) {
        case SDL_BUTTON_LEFT:
          onKeyrelease(KEY_MOUSE_LEFT);
          break;

        case SDL_BUTTON_MIDDLE:
          onKeyrelease(KEY_MOUSE_MIDDLE);
          break;

        case SDL_BUTTON_RIGHT:
          onKeyrelease(KEY_MOUSE_RIGHT);
          break;
      }
    }

    else if (event.type == SDL_KEYDOWN) {
      if (translateKey(event.key.keysym.sym)) {
        onKeypress(translateKey(event.key.keysym.sym));
      }
    }

    else if (event.type == SDL_KEYUP) {
      if (translateKey(event.key.keysym.sym)) {
        onKeyrelease(translateKey(event.key.keysym.sym));
      }
    }
  }
}

#endif
