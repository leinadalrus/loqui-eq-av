#ifndef AL_PL_PLAYER_H
#define AL_PL_PLAYER_H

#include <includes/proj_rsrc_ctl.h>
#include <rlimgui.h>
#include <raylib.h>
#include <imgui.h>

typedef struct OpenPLAL_ctx {} OpenPLAL_ctx;

#include <AL/alc.h>
#include <AL/al.h>
#include <AL/alext.h>

#include <common/alhelpers.h>

/*typedef struct*/ class OpenPLAL_t {
public:
  OpenPLAL_t(const char *filename, int texture_mode);
  void update_prog_self(OpenPLAL_t *self);
  void destroy_prog_self(OpenPLAL_t *self);

  GLuint compile_shader_proc(GLuint index, const char *source);
  GLuint create_texture_proc(GLuint index, const char *filename);
  void update_texture_proc(GLuint unit, GLuint texture, plm_plane_t *plane);

  void video_procs_on(plm_t *player, plm_frame_t *frame, char *data);
  void audio_procs_on(plm_t *player, plm_samples_t *samples, char *data);

private:
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
} /*OPEN_PLAL_t*/;

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