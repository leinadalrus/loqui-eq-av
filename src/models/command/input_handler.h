#include "handler_base_model.h"
#include "/./../entity/player/player_entity.h"

class InputHandler: public HandlerModel {
public:
  void handleInput();

private:
  CommandModel *moveRight;
  CommandModel *moveLeft;
  CommandModel *moveDown;
  CommandModel *moveUp;

  PlayerEntity *player;
};