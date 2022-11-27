#include "open_plal_t.h"

#define PL_MPEG_IMPLEMENTATION
#include <pl_mpeg.h>

OPEN_PLAL_T *create_app_w_params(const char *filename, int texture_mode);
void update_prog_self(OPEN_PLAL_t *self);
void destroy_prog_self(OPEN_PLAL_t *self);

GLuint compile_shader_proc(OPEN_PLAL_t *self, GLuint index, const char *source);
GLuint create_texture_proc(OPEN_PLAL_t *self, GLuint index, const char *filename);
void update_texture_proc(OPEN_PLAL_t *self, GLuint unit, GLuint texture, plm_plane_t *plane);

void video_procs_on(plm_t *player, plm_frame_t *frame, char *data);
void audio_procs_on(plm_t *player, plm_samples_t *samples, char *data);

const char *source_shader(Vector2 vertex_attrs, vector2 tex_coords) {
  return (char*) {
    tex_coord = vertex_attrs;
    // (x, y, z, alpha);
    gl_Position = vec4((vertex_attrs * 2.0 - 1.0) * vec2(1, -1), 0.0, 1.0);
  };
}

const char *frag_shader(Texture2D texture_y,
                        Texture2D texture_cb,
                        Texture2D texture_cr,
                        Vector2 tex_coord) {
  mat4 rec601 = mat4(1.16438,  0.00000,  1.59603, -0.87079,
                     1.16438, -0.39176, -0.81297,  0.52959,
                     1.16438,  2.01723,  0.00000, -1.08139,
                     0, 0, 0, 1);
  
  return (char*) {
    float y = (Texture2D)(texture_y, tex_coord).r;
    float cb = (Texture2D)(texture_cb, tex_coord).r;
    float cr = (Texture2D)(texture_cr, tex_coord).r;
    
    gl_FragColor = vec4(y, cb, cr, 1.0) * rec601;
  };
}

const char * source_shader_rgb(Texture2D texture_rgb;
                               Vector2 tex_coord) {
  return (char*) {
    gl_FragColor = vec4((Texture2D)(texture_rgba, tex_coords).rgb, 1.0);
  };
}

HWindConfigImpl::HWindConfigImpl(){}

HWindConfigImpl::~HWindConfigImpl(){}

char *HWindConfigImpl::create_on_demand() {
  char *ret_value;
  
  return ret_value;
}

char *HWindConfigImpl::read_internal_args(char **args) {
  struct *driver_data;
  
  return driver_data;
}

int HWindConfigImpl::driver_update_entities(struct *driver_data) {
  return 0;
}

void *HWindConfigImpl::kill_and_destroy(void *destruct_on_deficit) {}