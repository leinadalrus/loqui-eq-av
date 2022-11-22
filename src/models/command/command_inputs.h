#include "command_base_model.h"

#ifndef COMMAND_INPUTS_H
#define COMMAND_INPUTS_H

class MoveCommand: public CommandModel {
public:
  void Execute() {
    move();
  }
  void move();
};

#endif