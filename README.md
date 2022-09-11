## nano
> A small game engine written from scratch using C

<!-- ### Features
#### Window Creation
* Create a window with a title and dimensions
* Specify window attributes (e.g. fullscreen, vsync, etc)
* Specify the step function (which is ran every frame)
* Specify the load function (which is window creation)
* Update window attributes (e.g. title, dimensions, vsync, etc)
* Close the application

```c
#define NANITE_IMPLEMENTATION
#include "nanite.h"

/**
 * @brief Simple Implementation
 */
int WinMain(void) {
  // Specify window attributes
  Application app = {
    .title = "Hello World",
    .width = 640,
    .height = 480,

    .vsync = true,
    .fullscreen = false,
  };

  run(&app);
  return 0;
}
```

#### Basic Input Handling
* Handle keyboard input
* Handle window close events

```c
#define NANITE_IMPLEMENTATION
#include "nanite.h"

static void frame(void);

/**
 * @brief Simple Implementation
 */
static Application app;
int WinMain(void) {
  // Specify the step function (which is ran every frame)
  app.step = frame;
  run(&app);
  return 0;
}

static void frame(void) {
  // Exit if 'ESCAPE' is pressed
  if (keypress(KEY_ESCAPE))
    app.running = false;

  // Toggle fullscreen if 'F' is pressed
  if (keypress(KEY_F))
    setFullscreen(&app);
}
```

#### Rendering
* Render a simple shader

```c
#define NANITE_IMPLEMENTATION
#include "nanite.h"

static void load(void);

/**
 * @brief Simple Implementation
 */
static Application app;
int WinMain(void) {
  // Specify the load function (which is ran on window creation)
  app.load = load;
  run(&app);
  return 0;
}

static void load(void) {
  // Create an entity and a shader
  createEntity("Entity", (int[2]) {4, 4}, (float[3]) {0.0f, 0.0f, 0.0f});
  createShader("Entity", "shaders/basic.vert", "shaders/basic.frag");
}
``` -->

<!-- ### Planned Features -->

### Current Dependencies
* [SDL2](https://www.libsdl.org/release/)
* [GLEW](https://glew.sourceforge.net/basic.html)
* [Sean Barrett's Image Header Library](https://github.com/nothings/stb)
