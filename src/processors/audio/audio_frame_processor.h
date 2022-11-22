#ifdef __GNUC__
_Pragma("GCC diagnostic push")
_Pragma("GCC diagnostic ignored \"-Wconversion\"")
_Pragma("GCC diagnostic ignored \"-Wold-style-cast\"")
#endif

extern "C" {
#include "raylib.h"

#include "../../lib/openalsoft/include/AL/al.h"
#include "../../lib/openalsoft/include/AL/alc.h"
#include "../../lib/openalsoft/include/AL/alext.h"

#include "../../lib/libsndfile/include/sndfile.h"
}

#ifndef AUDIO_FRAME_PROCESSOR_H
#define AUDIO_FRAME_PROCESSOR_H

#include <stdlib.h>         // Required for: malloc(), free() ...
#include <math.h>           // Required for: sinf() ...
#include <string.h>         // Required for: memcpy() ...
#include <array>

#include "./src/models/dsp/biquad_filter.h"
#include "./src/models/dsp/three_band_eq.h"

#include "../shared/data/audio_data_types.h"
#include "../shared/data/hrtf_process_data.h"

#include "../shared/data/device_config.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846

#define MAX_SAMPLES               512
#define MAX_SAMPLES_PER_UPDATE   4096

class AudioFrameProcessor: public BiquadFilter {
public:
  AudioFrameProcessor(BiquadFilter biquad): biquadFilter(biquad) {}
  ~AudioFrameProcessor();
  
  BiquadFilter *GetBiquadFilter();
  ALuint LoadItems(SF_INFO *soundInfos);
  void ConfigureDevice(AudioInterface::DeviceConfig *deviceConfig);
  ALdouble ProcessAudioSample(double xn);

private: // Private Members:
  BiquadFilter *biquadFilter;
  AudioInterface::DeviceConfig *deviceConfig;
  std::array<ALdouble, 2> alDAngles; // angles are equal to stereo channels
  SNDFILE *sndfile;
  // Private Functions:
  ALdouble ProcessSampleSet(std::array<double, 0xFF>& inputSample);
};

#endif // AUDIO_FRAME_PROCESSOR_H

