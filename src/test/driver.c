#include "nano/Input.h"
#include "nano/Systems.h"
#include "nano/Application.h"

static void load(void);
static void frame(void);

static float now;
static float last;
static float delta;

Entity player;
static Application app;
int WinMain(int argc, char const *argv[]) {
  app.fps = 60;
  app.width = 640;
  app.height = 360;
  app.load = load;
  app.step = frame;
  app.title = "Sacrifice";
  start(&app);

  last = time();
  while (!app.quit) {
    resetInput();

    now = time();
    delta = now - last;

    if (delta > (1000 / app.fps)) {
      last = now;
      inputProc(&app);

      frame();
      clear(NULL);
      renderSprites(app.ecs);
      draw(&app);
    }
  }

  close(&app);
  return 0;
}

static void frame(void) {
  if (keypress(KEY_ESCAPE))
    app.quit = true;

  if (keypress(KEY_W) || keypress(KEY_UP))
    updatePlayerPosition(app.ecs, player, UP, 1.0f);

  if (keypress(KEY_S) || keypress(KEY_DOWN))
    updatePlayerPosition(app.ecs, player, DOWN, 1.0f);

  if (keypress(KEY_A) || keypress(KEY_LEFT))
    updatePlayerPosition(app.ecs, player, LEFT, 1.0f);

  if (keypress(KEY_D) || keypress(KEY_RIGHT))
    updatePlayerPosition(app.ecs, player, RIGHT, 1.0f);
}

static void load(void) {
  player = createEntity(app.ecs);
  createComponent(app.ecs, player, GRAVITY, NULL);
  createComponent(app.ecs, player, RIGIDBODY, NULL, NULL);
  createComponent(app.ecs, player, TRANSFORM, NULL, NULL, NULL);
  createComponent(app.ecs, player, SHADER, "assets/shaders/basic.vs", "assets/shaders/basic.fs");
  createComponent(app.ecs, player, TEXTURE, "assets/textures/player.png");
}
