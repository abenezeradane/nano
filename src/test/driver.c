#include "nano/Input.h"
#include "nano/Utility.h"
#include "nano/Application.h"

static float now;
static float last;
static float delta;

static void load(void);
static void frame(void);

static Application app = {0};
static Renderer renderer = {0};
int WinMain(int argc, char const *argv[]) {
  app.title = "Sacrifice";
  app.fps = 30;
  app.width = 512;
  app.height = 256;
  app.load = load;
  app.step = frame;
  app.quit = false;
  renderer.projection = morthographic(0.0f, app.width, app.height, 0.0f, 0.0f, 100.0f);
  app.renderer = &renderer;
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
  createshader(&renderer, "test.vert", "test.frag");
  // float test[] = {
  //    (1.0f / 20),  ((float) (app.width / app.height) / 20), 0.0f,
  //    (1.0f / 20), -((float) (app.width / app.height) / 20), 0.0f,
  //   -(1.0f / 20), -((float) (app.width / app.height) / 20), 0.0f,
  //   -(1.0f / 20),  ((float) (app.width / app.height) / 20), 0.0f
  // };
}
