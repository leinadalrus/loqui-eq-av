#ifndef IMMEDIATE_RGUI_H
#define IMMEDIATE_RGUI_H

#include <raylib.h>
#include <raymath.h>

#include <imgui.h>

#include <rlimgui/rlImGui.h>
#include <rlimgui/rlImGuiColors.h>

int const HasQuit(int isQuitting) { return isQuitting; }

int const ImmediateWindowOpened(int isOpened) { return isOpened; }

int const ImmediateWindowFocused(int isFocused) { return isFocused; }

enum class EntityStates { UNDEFINED, STATIC, DYNAMIC };

class ImmediateRGUI {
public:
  ImmediateRGUI();

  int ShuttingDown();
  int Showing();
  int Updating();

private:
  int isWindowOpened = ImmediateWindowOpened(0);
  int isWindowFocused = ImmediateWindowFocused(0);

  Camera2D camera2D = {0};
  Texture imageTexture = {0};
  Texture2D baseTexture = {0};
  Texture2D viewportTexture = {0};
  EntityStates currentState = EntityStates::UNDEFINED;

  Vector2 lastMousePos = {0};
  Vector2 lastTarget = {0};
  int isDragging = false;
  int isDirty = false;

  int MainMenu();
};

#endif // IMMEDIATE_RGUI_H