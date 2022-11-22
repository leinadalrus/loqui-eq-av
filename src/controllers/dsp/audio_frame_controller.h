#include <iostream>

#include <C:\raylib\raylib\src\raylib.h>
#include <C:\raylib\raylib\src\raymath.h>

#include "../../includes/src_main.h"
#include "/./models/dsp/biquad_filter.h"
#include "../processors/audio/audio_frame_processor.h"
#include "../../lib/libsndfile-1.1.0/include/sndfile.hh"

#ifndef AUDIO_FRAME_WHEEL_H
#define AUDIO_FRAME_WHEEL_H

class AudioFrameController {
public:
  AudioFrameController(BiquadFilter *biquad) : biquadFilter(biquad) {}
  ~AudioFrameController();
  
  short *audioInputCallback(short* buffer, unsigned int frames);
  short *audioInputCallback();
  int processAudioSample(double sampleXN);

  BiquadFilter *getBiquadFilter () { return biquadFilter; }

private:
  BiquadFilter *biquadFilter = new BiquadFilter;
};

#endif // AUDIO_FRAME_WHEEL_H