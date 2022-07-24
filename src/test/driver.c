#include "nano/Application.h"
#include "nano/Input.h"
#include "nano/Math.h"

static float now;
static float last;
static float delta;

static void load(void);
static void frame(void);

Application app = {0};
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
  app.title = "Sacrifice";
  app.fps = 60;
  app.width = 500;
  app.height = 400;
  app.load = load;
  app.step = frame;
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

  close(&app);
  return 0;
}

static void frame(void) {
  if (keypress(KEY_ESCAPE))
    quit(&app);

  clear(0);
  render(&app);
}

static void load(void) {

}
