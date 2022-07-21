#include "nano/Application.h"
#include "nano/Input.h"

static float delta;
static unsigned int now;
static unsigned int last;

static void load(void);
static void frame(void);

int WinMain(int argc, char *argv[]) {
  Application app = {0};
  app.title = "Illusion";
  app.fps = 60;
  app.width = 500;
  app.height = 400;
  app.load = load;
  app.quit = false;
  start(&app);

  last = SDL_GetTicks();
  while (!app.quit) {
    resetInput();

    now = SDL_GetTicks();
    delta = (float) (now - last);

    if (delta > (1000 / app.fps)) {
      last = now;
      inputproc(&app);
      frame();
    }
  }

  return 0;
}

static void frame(void) {

}

static void load(void) {

}
