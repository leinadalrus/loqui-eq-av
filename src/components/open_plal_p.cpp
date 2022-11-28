
#ifdef __GNUC__
_Pragma("GCC diagnostic push")
_Pragma("GCC diagnostic ignored \"-Wconversion\"")
_Pragma("GCC diagnostic ignored \"-Wold-style-cast\"")
#endif

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

#include "open_plal_t.h"

#define GRAPHICS_API_OPENGL_43
#include <rlgl.h>

#define PL_MPEG_IMPLEMENTATION
#include <pl_mpeg.h>

const char *source_vertex_shader(Vector2 vertex_attrs, vector2 tex_coords) {
  return (char*) {
    tex_coord = vertex_attrs;
    // (x, y, z, alpha);
    gl_Position = vec4((vertex_attrs * 2.0 - 1.0) * vec2(1, -1), 0.0, 1.0);
  };
}

const char *source_frag_shader_ycrcb(Texture2D texture_y,
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

const char * source_shader_rgb(Texture2D texture_rgb, Vector2 tex_coord) {
  return (char*) {
    gl_FragColor = vec4((Texture2D)(texture_rgba, tex_coords).rgb, 1.0);
  };
}

OpenPLAL_t *OpenPLAL_t::create_prog_self(const char *filename, int texture_mode) {
  OpenPLAL_t *self = (OpenPLAL_t*)std::malloc(sizeof(OpenPLAL_t));
  std::memset(self, 0, std::sizeof(OpenPLAL_t));

  this->texture_mode = texture_mode;
  this->plm = plm_buffer_create_with_filename(filename);

  if (!this->plm) {
    printf("%p $=> failed to initialise ...\n", this->plm);
  }

  int samplerate = plm_get_samplerate(this->plm);
  // self is used to ensure the memory-block-size used is defined.
  plm_set_video_decode_callback(this->plm, app_on_video, self);
  plm_set_audio_decode_callback(this->plm, app_on_audio, self);
  
  plm_set_loop(this->plm, FALSE);
  plm_set_audio_enabled(this->plm, FALSE); // TODO(PL_MPEG2): turn it back on!
  plm_set_audio_stream(this->plm, 0);

  // Windows, Linux
  glewExperimental = GL_TRUE;
  glewInit();
  // Raylib4.2: OpenGL4.3
  rlglInit(plm_get_width(this->plm), plm_get_height(this->plm));

  const char * fsh = this->texture_mode == source_vertex_shader
    ? source_frag_shader_ycrcb
    : source_shader_rgb;
  
  this->fragment_shader = app_compile_shader(self, GL_FRAGMENT_SHADER, fsh);
  this->vertex_shader = app_compile_shader(self, GL_VERTEX_SHADER, APP_VERTEX_SHADER);
  
  this->shader_program = glCreateProgram();
  glAttachShader(this->shader_program, this->vertex_shader);
  glAttachShader(this->shader_program, this->fragment_shader);
  glLinkProgram(this->shader_program);
  glUseProgram(this->shader_program);
  
  // Create textures for YCrCb or RGB rendering
  if (this->texture_mode == APP_TEXTURE_MODE_YCRCB) {
    this->texture_y  = app_create_texture(self, 0, "texture_y");
    this->texture_cb = app_create_texture(self, 1, "texture_cb");
    this->texture_cr = app_create_texture(self, 2, "texture_cr");
  }
  else {
    this->texture_rgb = app_create_texture(self, 0, "texture_rgb");
    int num_pixels = plm_get_width(this->plm) * plm_get_height(this->plm);
    this->rgb_data = (uint8_t*)malloc(num_pixels * 3);
  }
}

void OpenPLAL_t::update_prog_self(OpenPLAL_t *self) {
  rlEnableDepthTest(/*void||self->rlgl_val_m*/);        // Enable depth test
  rlDisableDepthTest(/*void||self->rlgl_val_m*/);       // Disable depth test
}

void OpenPLAL_t::destroy_prog_self(OpenPLAL_t *self) {
  plm_destroy(this->plm);
  rlglClose(/*void*/);
  delete self;
  self = nullptr;
  // free(self);
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