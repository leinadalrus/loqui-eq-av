#ifndef AL_PL_PLAYER_H
#define AL_PL_PLAYER_H

#include <includes/src_main.h>
#include <rlimgui.h>
#include <raylib.h>
#include <imgui.h>

#ifdef __GNUC__
_Pragma("GCC diagnostic push")
_Pragma("GCC diagnostic ignored \"-Wconversion\"")
_Pragma("GCC diagnostic ignored \"-Wold-style-cast\"")
#endif

typedef struct OpenPLAL_ctx {} OPEN_PLAL_ctx;

#include <AL/alc.h>
#include <AL/al.h>
#include <AL/alext.h>

#include <common/alhelpers.h>

typedef struct OpenPLAL_t {
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
} OPEN_PLAL_t;

class HWindConfigImpl: public OpenPLAL_t {
public:
  HWindConfigImpl_t();
  ~HWindConfigImpl_t();
  
  char *create_on_demand();
  char *read_internal_args(char **args);
  int driver_update_entities(struct *driver_data);
  void *kill_and_destroy(void *destruct_on_deficit);
  
private:
  char *known_memory_offset = (char *)0;
  unsigned int hwind_item_uuid = 0;
  std::string hwind_item_title = "";

  OpenPLAL_t *open_plal_self = {0};
};

#endif