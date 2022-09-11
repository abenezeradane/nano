#define NANITE_IMPLEMENTATION
#include "nano\nanite.h"

static void load(void);
static void frame(void);

static Application app;
int WinMain(int argc, char const *argv[]) {
  app.title = "Noir";
  app.width = 640;
  app.height = 480;

  app.load = load;
  app.step = frame;

  run(&app);
  return 0;
}

static void load(void) {
  // Create a 'Player' entity and add a basic shader to it
  createEntity("Player", (int[2]) {3, 4}, (float[3]) {0.0f, 0.0f, 0.0f});
  createShader("Player", "data/shaders/basic.vert", "data/shaders/basic.frag");
}

static void frame(void) {
  // Exit if 'ESCAPE' is pressed
  if (keypress(KEY_ESCAPE))
    app.running = false;

  if (keypress(KEY_LALT)) // TODO: Remove this after testing
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  else
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  // Toggle fullscreen if 'F' is pressed
  if (keypress(KEY_F))
    setFullscreen(&app);

  // Check if player is moving vertically
  if (keypress(KEY_W) && !keypress(KEY_A) && !keypress(KEY_D))
    updateEntityPosition("Player", (float[3]) {0.0f, 0.0175f, 0.0f});
  if (keypress(KEY_S) && !keypress(KEY_A) && !keypress(KEY_D))
    updateEntityPosition("Player", (float[3]) {0.0f, -0.0175f, 0.0f});

  // Check if player is moving horizontally
  if (keypress(KEY_A) && !keypress(KEY_W) && !keypress(KEY_S))
    updateEntityPosition("Player", (float[3]) {-0.0175f, 0.0f, 0.0f});
  if (keypress(KEY_D) && !keypress(KEY_W) && !keypress(KEY_S))
    updateEntityPosition("Player", (float[3]) {0.0175f, 0.0f, 0.0f});

  // Check if player is moving diagonally
  if (keypress(KEY_W) && keypress(KEY_A))
    updateEntityPosition("Player", (float[3]) {-0.012374, 0.012374f, 0.0f});
  if (keypress(KEY_W) && keypress(KEY_D))
    updateEntityPosition("Player", (float[3]) {0.012374f, 0.012374f, 0.0f});

  if (keypress(KEY_S) && keypress(KEY_A))
    updateEntityPosition("Player", (float[3]) {-0.012374f, -0.012374f, 0.0f});
  if (keypress(KEY_S) && keypress(KEY_D))
    updateEntityPosition("Player", (float[3]) {0.012374f, -0.012374f, 0.0f});
}