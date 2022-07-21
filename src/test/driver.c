#include "nano/Application.h"
#include "nano/Input.h"

static void load(void);
static void frame(void);

int WinMain(int argc, char *argv[]) {
  Application app = {0};
  app.title = "Illusion";
  app.width = 450;
  app.height = 450;
  app.step = frame;
  app.load = load;
  app.quit = false;
  start(&app);

  while (!app.quit) {
    resetInput();
    inputproc(&app);
    frame();
  }

  return 0;
}

static void frame(void) {
  if (keypress(KEY_ESCAPE))
    SDL_Quit();
}

static void load(void) {

}
