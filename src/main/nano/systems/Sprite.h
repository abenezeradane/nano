#ifndef SPRITE_H
#define SPRITE_H

#include "../ECS.h"

#define XTILES 32 / 2
#define YTILES 18 / 2

void renderSprites(ECS* ecs) {
  if (!ecs)
    return;

  for (Entity entity = 0; entity < (ecs -> entities -> count); entity++) {
    if (isLiving(ecs, entity)) {
      Shader* shader = (Shader*) getComponent(ecs, entity, SHADER);
      Texture* texture = (Texture*) getComponent(ecs, entity, TEXTURE);
      Transform* transform = (Transform*) getComponent(ecs, entity, TRANSFORM);

      if (!shader || !transform)
        continue;

      unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
      };

      if (!(shader -> generated)) {
        glGenVertexArrays(1, &(shader -> VAO));
        glGenBuffers(1, &(shader -> VBO));
        glGenBuffers(1, &(shader -> EBO));
        glBindVertexArray(shader -> VAO);
        shader -> generated = 1;
      }

      if (!texture) {
        float vertices[] = {
          (((transform -> position)[0] + 0.5f) / (XTILES / 2)), (((transform -> position)[1] + 0.5f) / (YTILES / 2)), 0.0f,   1.0f, 0.0f, 0.0f,
          (((transform -> position)[0] + 0.5f) / (XTILES / 2)), (((transform -> position)[1] - 0.5f) / (YTILES / 2)), 0.0f,   1.0f, 1.0f, 0.0f,
          (((transform -> position)[0] - 0.5f) / (XTILES / 2)), (((transform -> position)[1] - 0.5f) / (YTILES / 2)), 0.0f,   0.0f, 1.0f, 0.0f,
          (((transform -> position)[0] - 0.5f) / (XTILES / 2)), (((transform -> position)[1] + 0.5f) / (YTILES / 2)), 0.0f,   0.0f, 0.0f, 1.0f,
        };

        glBindBuffer(GL_ARRAY_BUFFER, shader -> VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shader -> EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);
      } else {
        float vertices[] = {
          (((transform -> position)[0] + 0.5f) / (XTILES / 2)), (((transform -> position)[1] + 0.5f) / (YTILES / 2)), 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
          (((transform -> position)[0] + 0.5f) / (XTILES / 2)), (((transform -> position)[1] - 0.5f) / (YTILES / 2)), 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f,
          (((transform -> position)[0] - 0.5f) / (XTILES / 2)), (((transform -> position)[1] - 0.5f) / (YTILES / 2)), 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
          (((transform -> position)[0] - 0.5f) / (XTILES / 2)), (((transform -> position)[1] + 0.5f) / (YTILES / 2)), 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f,
        };

        glBindBuffer(GL_ARRAY_BUFFER, shader -> VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shader -> EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (6 * sizeof(float)));
        glEnableVertexAttribArray(2);
      }

      if (texture)
        glBindTexture(GL_TEXTURE_2D, texture -> data);

      glClear(GL_COLOR_BUFFER_BIT);
      glUseProgram(shader -> data);
      glBindVertexArray(shader -> VAO);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
  }
}

#endif
