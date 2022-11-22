#include "C:\\raylib\\raylib\\src\\raylib.h"

#ifndef COMMAND_BASE_MODEL_H
#define COMMAND_BASE_MODEL_H

class CommandModel {
public:
  CommandModel();
  void Execute() = 0;
};

#endif // BOY_PFKS_COMMAND_BASE_MODEL_H