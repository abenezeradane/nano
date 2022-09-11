#define NANITE_IMPLEMENTATION
#include "nano\nanite.h"

static void load(void);
static void frame(void);

static Application app;
int WinMain(int argc, char const *argv[]) {
  app.title = "Noir";
  app.width = 1280;
  app.height = 720;

  app.load = load;
  app.step = frame;

  run(&app);
  return 0;
}

static void load(void) {
  // Create a 'Player' entity and add a basic shader to it
  createEntity("Player", (int[2]) {2, 5}, (float[3]) {-0.75f, -0.125f, 0.0f});
  createShader("Player", "data/shaders/basic.vert", "data/shaders/basic.frag");
}

static void frame(void) {
  // Exit if 'ESCAPE' is pressed
  if (keypress(KEY_ESCAPE))
    app.running = false;

  // Check if 'A' or 'D' is pressed
  if (keypress(KEY_A))
    updateEntityPosition("Player", (float[3]) {-0.00625f, 0.0f, 0.0f});

  if (keypress(KEY_D))
    updateEntityPosition("Player", (float[3]) {0.00625f, 0.0f, 0.0f});
}