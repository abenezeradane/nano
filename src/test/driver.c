#include "nano/Application.h"

static void load(void);
static void frame(void);

int WinMain(int argc, char *argv[]) {
  Application app = {0};
  app.title = "Illusion";
  app.width = 450;
  app.height = 450;
  app.step = frame;
  app.load = load;
  start(&app);

  return 0;
}

static void frame(void) {

}

static void load(void) {
  SDL_Delay(5000);
  SDL_Quit();
}
