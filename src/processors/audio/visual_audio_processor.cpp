#include "visual_audio_processor.h"
#include "audio_frame_processor.h"

#include <assert>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>

#if defined(__APPLE__) && defined(__MACH__)
  // OSX
  #include <OpenGL/gl.h>
  #include <OpenGL/glext.h>

  void glCreateTextures(GLuint ignored, GLsizei n, GLuint *name) {
    glGenTextures(1, name);
  }
#elif defined(__unix__)
  // Linux
  #include <GL/glew.h>
#else
  // WINDOWS
  #include <windows.h>

  #define GL3_PROTOTYPES 1
  #include <glew.h>
  #pragma comment(lib, "glew32.lib")

  #include <gl/GL.h>
  #pragma comment(lib, "opengl32.lib")
#endif

#define PL_MPEG_IMPLEMENTATION
#include "plmpeg.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
// #define STBIW_ASSERT(x)
// #define STBIW_MALLOC()
// #define STBIW_REALLOC()
// #define STBIW_FREE()
// #define STBIW_MEMMOVE()
#include "stb_image_write.h"

#define STBIW_WINDOWS_UTF8

void VisualAudioProcessor::frameCallback(plm_t *plm, plm_frame_t *frame, void *data) {
  // frame->y.data;
  // frame->cr.data;
  // frame->cb.data;
}

void VisualAudioProcessor::audioCallback(plm_t *plm, plm_frame_t *frame, void *data) {
  // samples->interleaved;
}

int VisualAudioProcessor::processCallbacks(plm_t *plm) {
  plm_set_audio_enabled(plm, FALSE);
  // stbiw_convert_wchar_to_utf8() // to convert wchar to utf8
  
  int w = plm_get_width(plm);
  int h = plm_get_height(plm);
  uint8_t *rgb_buffer = (uint8_t *)std::malloc(w * h * 3);
  
  char bmp_filename[16];
  plm_frame_t *frame = nullptr;

  std::fstream ofstream;
  ofstream.open(&bmp_filename, std::fstream::trunc);
  while (ofstream.is_open()) {
    for (int i = 1; frame = plm_decode_video(plm); i++) {
      plm_frame_to_rgb(frame, rgb_buffer, w * 3);

      std::sprintf(png_name, "%06d.bmp", i);
      std::printf("Writing %s\n", bmp_filename);
      stbi_write_bmp(bmp_filename, w, h, 3, rgb_buffer);

      // stbi_write_bmp_to_func(); // arbitrary write function
    }
  }

  ofstream.close();

  /**
   * There are also five equivalent functions that use an arbitrary write function. 
   * You are
   expected to open/close your file-equivalent before and after calling these:
   *
   * 
   * int stbi_write_bmp_to_func(stbi_write_func *func, void *context, int w, int h, int comp, const void  *data);
   * 
   * where the callback is:
      void stbi_write_func(void *context, void *data, int size);
   */

  return 0;
}