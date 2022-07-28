#include "nano/Input.h"
#include "nano/Utility.h"
#include "nano/Application.h"

static float now;
static float last;
static float delta;

static void load(void);
static void frame(void);

static Application app;
static Renderer renderer;
static ECS ecs;
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

  ecs.entities = entitymanager();
  ecs.components = componentmanager();
  app.ecs = &ecs;

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

  {
    #include <stdio.h>
    Entity test = newentity(&ecs);
    Component testposition = newcomponent(POSITION);
    float* position = getposition(&testposition);
    printf("Unassigned Position: (%.2f, %.2f)\n", position[0], position[1]);
    assigncomponent(&ecs, testposition, test);
    Component get = getcomponent(&ecs, test, POSITION);
    setposition(&get, 1.0f, 1.0f);
    position = getposition(&get);
    printf("Unassigned Position: (%.2f, %.2f)\n", position[0], position[1]);
  }
}
