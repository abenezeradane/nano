#include "nano/Application.h"
#include "nano/Input.h"
#include "nano/Math.h"
#include "nano/util/Filereader.h"

static float now;
static float last;
static float delta;

static void load(void);
static void frame(void);

static Color PALETTE[4] = {
  {0.80f, 0.65f, 0.43f, 1.0f},
  {0.60f, 0.41f, 0.24f, 1.0f},
  {0.20f, 0.16f, 0.13f, 1.0f},
  {0.40f, 0.29f, 0.19f, 1.0f}
};

static Application app = {0};
int WinMain(int argc, char const *argv[]) {
  Renderer renderer = {
    .vertex = readfile("test.vert"),
    .fragment = readfile("test.frag")
  };

  app.title = "Sacrifice";
  app.fps = 60;
  app.width = 500;
  app.height = 400;
  app.load = load;
  app.step = frame;
  app.quit = false;
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

  clear(&PALETTE[3]);
  render(&app);
}

static void load(void) {
  float triangle[] = {
    1, 0, 0, 1, 0, 0,
    0, 1, 0, 1, app.width, 0,
    0, 0, 1, 1, app.width, app.height,

    1, 0, 0, 1, 0, 0,
    0, 0, 1, 1, app.width, app.height,
    1, 1, 1, 1, 0, app.height
  };
}
