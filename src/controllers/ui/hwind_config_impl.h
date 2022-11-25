#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <string>
#include <cstring>
#include <iostream>

#include <imgui.h>
#include <raylib.h>
#include <rlimgui.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>
#include <sndfile.hh>

#if defined(__unix__)\

#include <GL/glew.h>

#else

#include <windows.h>
#include <glew.h>

#define GL3_PROTOTYPES 1
#include <glew.h>
#pragma comment(lib, "glew32.lib")

#include <gl/GL.h>
#pragma comment(lib, "opengl32.lib")

#include <rlgl.h>
#pragma comment(lib, "raylib.lib")

#endif

#ifndef HWIND_CONFIG_IMPL_H
#define HWIND_CONFIG_IMPL_H

class HWindConfigImpl {
  public:
  HWindConfigImpl();
  ~HWindConfigImpl();
  
  char *create_on_demand();
  struct *read_internal_args(char **args);
  int driver_update_entities(struct *driver_data);
  void *kill_and_destroy(void *destruct_on_deficit);
  
  private:
  char *known_memory_offset = (char *)0;
  unsigned int hwind_item_uuid = 0;
  std::string hwind_item_title = "";
};

typedef struct AppConfigImpl_t {
  plm_t *plm;
  // SDL_Window *window;
  // SDL_AudioDeviceID audio_device;
  
  // OpenGL context:
  // SDL_GLContext gl;
  GLuint shader_program;
  GLuint vertex_shader;
  GLuint fragment_shader;

  // OpenGL texture:
  int texture_mode;
  GLuint texture_y;
  GLuint texture_cb;
  GLuint texture_cr;

  GLuint texture_rgb;
  uint8_t *rgb_data;
} AppConfigImpl_t;

#endif // HWIND_CONFIG_IMPL_H