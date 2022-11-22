#include <iostream>

#include <C:\raylib\raylib\src\raylib.h>
#include <C:\raylib\raylib\src\raymath.h>

#include "pfks.h"
#include "/./models/dsp/biquad_filter.h"
#include "/./proc/hart_strung_processor.h"
#include "libsndfile/include/sndfile.h"

#ifndef AUDIO_FRAME_WHEEL_H
#define AUDIO_FRAME_WHEEL_H

class AudioFrameController {
public:
  AudioFrameController(BiquadFilter biquad) : biquadFilter(biquad) {}
  ~AudioFrameController();
  
  void audioInputCallback(short* buffer, unsigned int frames);
  int processAudioSample(double sampleXN);
private:
  BiquadFilter *biquadFilter = new BiquadFilter;
};

#endif // AUDIO_FRAME_WHEEL_H