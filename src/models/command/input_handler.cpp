#include "input_handler.h"

void InputHandler::handleInput() {
  if (IsKeyDown(KEY_RIGHT))
    player->position.x += 1.0f;
  if (IsKeyDown(KEY_LEFT))
    player->position.x -= 1.0f;
  if (IsKeyDown(KEY_UP))
    player->position.y += 1.0f;
  if (IsKeyDown(KEY_DOWN))
    player->position.y -= 1.0f;
}