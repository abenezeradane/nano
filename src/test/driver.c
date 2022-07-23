#include "nano/Application.h"
#include "nano/Input.h"
#include "nano/Math.h"

static float now;
static float last;
static float delta;

static void load(void);
static void frame(void);

int WinMain(int argc, char *argv[]) {
  Application app = {0};
  app.title = "Sacrifice";
  app.fps = 60;
  app.width = 500;
  app.height = 400;
  app.load = load;
  app.quit = false;
  start(&app);

  last = time();
  while (!app.quit) {
    resetInput();

    now = time();
    delta = now - last;

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
