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

  {
    if (keypress(KEY_W))
      printf("W");
    if (keypress(KEY_A))
      printf("A");
    if (keypress(KEY_S))
      printf("S");
    if (keypress(KEY_D))
      printf("D");
  }

  clear(0);
  render(&app);
}

static void load(void) {
  Entity player = newentity(&ecs);
  Component playerposition = newcomponent(POSITION, NULL);
  SPRITEDATA* data = (SPRITEDATA*) malloc(sizeof(SPRITEDATA));
  data -> vertexfile = "test.vert";
  data -> fragmentfile = "test.frag";
  data -> texturefile = "test.png";
  data -> width = app.width;
  data -> height = app.height;
  Component playersprite = newcomponent(SPRITE, data);
  assigncomponent(&ecs, playersprite, player);
  free(data);
}
