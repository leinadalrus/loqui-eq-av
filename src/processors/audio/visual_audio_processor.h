#ifndef VISUAL_AUDIO_PROCESSOR_H
#define VISUAL_AUDIO_PROCESSOR_H

#include "./includes/src_main.h"

class VisualAudioProcessor {
public:
  void frameCallback(plm_t *plm, plm_frame_t *frame, void *data);

  void audioCallback(plm_t *plm, plm_frame_t *frame, void *data);

  int processCallbacks(plm_t *plm);
};


#endif // VISUAL_AUDIO_PROCESSOR_H