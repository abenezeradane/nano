#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../ECS.h"

#define MOVE_SPEED 0.375f

typedef enum Direction {
  UP, DOWN, RIGHT, LEFT
} Direction;

void updatePlayerPosition(ECS* ecs, Entity player, Direction direction, float delta) {
  if (!ecs)
    return;

  Transform* transform = (Transform*) getComponent(ecs, player, TRANSFORM);
  switch (direction) {
    case RIGHT:
      (transform -> position)[0] += (delta * MOVE_SPEED);
      printf("Player Position: (%.1f, %.1f)\n", (transform -> position)[0], (transform -> position)[1]);
      break;

    case LEFT:
      (transform -> position)[0] -= (delta * MOVE_SPEED);
      printf("Player Position: (%.1f, %.1f)\n", (transform -> position)[0], (transform -> position)[1]);
      break;

    case UP:
      (transform -> position)[1] += (delta * MOVE_SPEED);
      printf("Player Position: (%.1f, %.1f)\n", (transform -> position)[0], (transform -> position)[1]);
      break;

    case DOWN:
      (transform -> position)[1] -= (delta * MOVE_SPEED);
      printf("Player Position: (%.1f, %.1f)\n", (transform -> position)[0], (transform -> position)[1]);
      break;
  }
}

#endif
