#include "immediate_rgui.h"

ImmediateRGUI::ImmediateRGUI() {
  SetConfigFlags(FLAG_MSAA_4X_HINT || FLAG_VSYNC_HINT);
  InitWindow(UNIVERSAL_WINDOW_SCREEN_WIDTH, UNIVERSAL_WINDOW_SCREEN_HEIGHT,
             UNIVERSAL_WINDOW_APP_TITLE);

  this->viewportTexture =
      LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

  this->camera2D.zoom = 1;
  
  this->camera2D.rotation = 0;
  this->camera2D.offset.x = GetScreenWidth() / 2.0f;
  this->camera2D.offset.y = GetScreenHeight() / 2.0f;

  Image img = GenImageChecked(256, 256, 32, 32, DARKGRAY, WHITE);
  this->baseTexture = LoadTextureFromImage(img);
  UnloadImage(img);
  GenTextureMipmaps(&this->baseTexture);
  SetTextureFilter(this->baseTexture, TEXTURE_FILTER_ANISOTROPIC_16X);
  SetTextureWrap(this->baseTexture, TEXTURE_WRAP_CLAMP);

  SetTargetFPS(61);

  rlImGuiSetup(true);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLANK);
    rlImGuiBegin(); // start window with GUI

    int isOpen = true;
    // ImGui::ShowDemoWindow(&isOpen);

    rlImGuiEnd(); // end window with GUI
    EndDrawing();
  }

  rlImGuiShutdown();
  CloseWindow();
}

int ImmediateRGUI::MainMenu() {
  if (ImGui::BeginMainMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      if (ImGui::MenuItem("Exit"))
        HasQuit(true);

      ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Window")) {
      ImGui::MenuItem("View", nullptr, &Scene2D.Open);

      ImGui::EndMenu();
    }
    
    ImGui::EndMainMenuBar();
  }

  return 0;
}

int ImmediateRGUI::Shutdown() {
  UnloadRenderTexture(this->viewportTexture);
  UnloadTexture(this->imageTexture);
  UnloadTexture(this->baseTexture);

  return 0;
}

int ImmediateRGUI::Render() {
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
  ImGui::SetNextWindowSizeConstraints(
      ImVec2(400, 400),
      ImVec2((float)GetScreenWidth(), (float)GetScreenHeight()));

  if (ImGui::Begin("3D View", &Open, ImGuiWindowFlags_NoScrollbar)) {
    this->isWindowFocused =
        ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows);

    ImVec2 size = ImGui::GetContentRegionAvail();

    Rectangle viewRect = {0};
    viewRect.x = this->viewportTexture.texture.width / 2 - size.x / 2;
    viewRect.y = this->viewportTexture.texture.height / 2 - size.y / 2;
    viewRect.width = size.x;
    viewRect.height = -size.y;

    if (ImGui::BeginChild("Toolbar",
                          ImVec2(ImGui::GetContentRegionAvail().x, 25))) {
      ImGui::SetCursorPosX(GetScreenWidth() / 2.0f);
      ImGui::SetCursorPosY(GetScreenHeight() / 2.0f);

      if (ImGui::Button("Undefined")) {
        this->curentState = EntityStates::UNDEFINED;
      }

      ImGui::SameLine();

      if (ImGui::Button("Static")) {
        this->curentState = EntityStates::DYNAMIC;
      }

      ImGui::SameLine();

      if (ImGui::Button("Dynamic")) {
        this->curentState = EntityStates::DYNAMIC;
      }

      ImGui::SameLine();

      switch (this->curentState) {
      case EntityStates::UNDEFINED:
        ImGui::TextUnformatted("Undefined");
        break;
      case EntityStates::STATIC:
        ImGui::TextUnformatted("Static");
        break;
      case EntityStates::DYNAMIC:
        ImGui::TextUnformatted("Dynamic");
        break;
      default:
        break;
      }

      ImGui::SameLine();
      ImGui::TextUnformatted(TextFormat("camera target X%f Y%f",
                                        Camera.target.x, Camera.target.y));
      ImGui::EndChild();
    }

    // draw the view
    rlImGuiImageRect(&ViewTexture.texture, (int)size.x, (int)size.y, viewRect);

    ImGui::End();
  }

  ImGui::PopStyleVar();

  return 0;
}

int ImmediateRGUI::Update() {

  if (!isWindowOpened)
    return;

  if (IsWindowResized()) {
    UnloadRenderTexture(this->viewportTexture);
    this->viewportTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

    this->camera2D.offset.x = GetScreenWidth() / 2.0f;
    this->camera2D.offset.y = GetScreenHeight() / 2.0f;
  }

  if (isWindowFocused) {
    if (currentState == EntityStates::DYNAMIC) {
      if (IsMouseButtonDown(0)) {
        if (!isDragging) {
          this->lastMousePos = GetMousePosition();
          this->lastTarget = this->camera2D.target;
        }
        Dragging = true;
        Vector2 mousePos = GetMousePosition();
        Vector2 mouseDelta = Vector2Subtract(this->lastMousePos, mousePos);

        mouseDelta.x /= this->camera2D.zoom;
        mouseDelta.y /= this->camera2D.zoom;
        this->camera2D.target = Vector2Add(this->lastTarget, mouseDelta);

        isDirty = true;

      } else {
        isDragging = false;
      }
    }
  } else {
    isDragging = false;
  }

  return 0;
}