#include "audio_frame_processor.h"

#include "../shared/io/normalized_values_converter.h"

AudioFrameProcessor::~AudioFrameProcessor() {}

template <typename T>
void cloneSamples(unsigned int *out, const unsigned int *in,
                  unsigned long long count, unsigned long long frameSize) {
  auto *sample = reinterpret_cast<const T *>(in);
  auto *destination = reinterpret_cast<T *>(out);
  if (frameSize == sizeof(T))
    std::fill_n(destination, count, *sample);
  else {
    size_t division = frameSize / sizeof(T);
    size_t deltaT = 0;
    std::generate_n(destination, count * division,
                    // lambda function:
                    [sample, division, &deltaT]() -> T {
                      T retVal = sample[deltaT];
                      deltaT = (deltaT + 1) % division;
                      return retVal;
                    });
  }
}

ALuint AudioFrameProcessor::LoadItems(SF_INFO *soundInfos) {
  ALuint bufbund = 0; // Buffer Bundle(s)
  /* 1 sample from each channel (PCM): */
  ALuint pcmSamplesPerFrame = soundInfos->samplerate / soundInfos->channels;
  // NOTE(Daniel): expr below is a possible loss of data in its conversion:
  unsigned int frameSize = soundInfos->frames * soundInfos->channels;
  unsigned int frameRate = soundInfos->samplerate / pcmSamplesPerFrame;
  
  while (pcmSamplesPerFrame > 0 && frameSize < pcmSamplesPerFrame) {
    bufbund = {pcmSamplesPerFrame};
    if (soundInfos->seekable >= 0) {
      auto const len =
        static_cast<unsigned int>(pcmSamplesPerFrame - soundInfos->seekable);
      if (bufbund > len)
        bufbund = len;
      
      auto soundInfosFrameSize = (unsigned int)soundInfos->frames * frameSize;
      
      std::memcpy(
                  reinterpret_cast<void *>(pcmSamplesPerFrame + soundInfosFrameSize),
                  reinterpret_cast<const void *>(bufbund * frameSize),
                  pcmSamplesPerFrame);
    } else {
      bufbund =
        std::min(bufbund, static_cast<unsigned int>(-soundInfos->seekable));
      
      /* Add samples by copying the first sample */
      if ((frameSize & 7) == 0)
        cloneSamples<unsigned long long>(
                                         /* samples */ &pcmSamplesPerFrame,
                                         /* mSamples */ &pcmSamplesPerFrame, bufbund, frameSize);
      else if ((frameSize & 3) == 0)
        cloneSamples<unsigned long long>(
                                         /* samples */ &pcmSamplesPerFrame,
                                         /* mSamples */ &pcmSamplesPerFrame, bufbund, frameSize);
      else if ((frameSize & 1) == 0)
        cloneSamples<unsigned long long>(
                                         /* samples */ &pcmSamplesPerFrame,
                                         /* mSamples */ &pcmSamplesPerFrame, bufbund, frameSize);
      else
        cloneSamples<unsigned long long>(
                                         /* samples */ &pcmSamplesPerFrame,
                                         /* mSamples */ &pcmSamplesPerFrame, bufbund, frameSize);
    }
    
    soundInfos->seekable += bufbund;
    // TODO(Automation): automation channel and poles
    auto cursors = int{static_cast<int>(bufbund)} / soundInfos->samplerate;
    pcmSamplesPerFrame += bufbund * frameSize;
    soundInfos /* +=audio size|> */ += bufbund;
    
    while (soundInfos->frames >= pcmSamplesPerFrame) {
      // pcmSamplesPerFrame = decodeFrame();
      soundInfos->seekable = std::min(pcmSamplesPerFrame, {0});
      if (pcmSamplesPerFrame <= 0)
        return 1;
      // soundInfos->seekable;
      
      // Adjust the device start time and current pts by the amount we're
      // skipping/duplicating, so that the clock remains correct for the
      // current stream position.
      auto skip = soundInfos->seekable / soundInfos->samplerate;
      if (deviceConfig->soundInfo->sections == 0 ||
          deviceConfig->soundInfo->sections == 1)
        deviceConfig->soundInfo->sections -= skip;
      soundInfos->seekable += skip;
      // Callback function here for continuation.
    }
  }
  
  if (frameSize <= 0)
    return 1;
  
  if (frameSize < pcmSamplesPerFrame) {
    bufbund = pcmSamplesPerFrame;
    
    std::memset(reinterpret_cast<void *>(pcmSamplesPerFrame),
                bufbund * frameSize,
                (soundInfos->format == SF_FORMAT_PCM_U8) ? 0x80 : 0x00);
    
    soundInfos->seekable += bufbund / soundInfos->samplerate;
  }
  
  return 0;
}

void AudioFrameProcessor::ConfigureDevice(
                                          AudioInterface::DeviceConfig *deviceConfig) {
  deviceConfig->alcContext = alcGetCurrentContext();
  deviceConfig->alcDevice = alcGetContextsDevice(deviceConfig->alcContext);
  AudioInterface::DeviceIDLoader deviceIDLoader;
  deviceIDLoader.LoadStringGetter(deviceConfig->alcDevice,
                                  deviceConfig->alcGetStringiSOFT,
                                  deviceConfig->alcGetStringiSOFT);
  deviceIDLoader.LoadDeviceReset(deviceConfig->alcDevice,
                                 deviceConfig->alcResetDeviceSOFT,
                                 deviceConfig->alcResetDeviceSOFT);
  
  ALenum eState;
  auto hasAngleExt = new ALboolean;
  
  HrtfProcessData hrtfProc;
  ALuint uSource = 0;
  
  ALuint alUBuffer = LoadItems(deviceConfig->soundInfo);
  // TODO(Daniel): load from an ,,.h'' file or a script or configuration file.
  alGenSources(1, &uSource);
  alSourcei(uSource, AL_SOURCE_RELATIVE, AL_TRUE);
  
  // have positions as data members
  alSource3f(uSource, AL_POSITION, 0.0f, 0.0f, -1.0f);
  alSourcei(uSource, AL_BUFFER, (ALint)alUBuffer);
  
  alSourcePlay(uSource);
  while (alGetError() == AL_NO_ERROR && eState == AL_PLAYING) {
    alcSuspendContext(deviceConfig->alcContext);
    
    /* Rotate the source around the listener by about 1/4 cycle per second,
     * and keep it within -pi...+pi.
     */
    hrtfProc.angle += 0.01 * M_PI * 0.5;
    if (hrtfProc.angle > M_PI)
      hrtfProc.angle -= M_PI * 2.0;
    
    /* This only rotates mono sounds. */
    alSource3f(uSource, AL_POSITION, (ALfloat)sin(hrtfProc.angle), 0.0f,
               -(ALfloat)cos(hrtfProc.angle));
    
    if (hasAngleExt) {
      /* This rotates stereo sounds with the AL_EXT_STEREO_ANGLES
       * extension. Angles are specified counter-clockwise in radians.
       */
      ALfloat angles1[2] = {(ALfloat)(M_PI * 2.0 - hrtfProc.angle),
        (ALfloat)(-M_PI / 6.0 - hrtfProc.angle)};
      
      ALfloat angles2[2] = {(ALfloat)(M_PI * 2.0 + hrtfProc.angle),
        (ALfloat)(M_PI * 2.0 + hrtfProc.angle)};
      
      alSourcefv(uSource, AL_STEREO_ANGLES, angles1);
      alSourcefv(uSource, AL_STEREO_ANGLES, angles2);
    }
    
    alcProcessContext(deviceConfig->alcContext);
    
    alGetSourcei(uSource, AL_SOURCE_STATE, &eState);
  }
  /* TODO(Daniel): Change the angling values to be a stored class members.
   * Change to have North-East-South-West coordinates
   *      to encompass the user in.
   * The 3D sound will be another dimension for audio mixing for input
   *      devices.
   * Currently the dAngle variable is acting as the actual ,,angle'' of the
   *      audio source itself. Therefore, we can either have multiple
   *      angles or have the angle channel multiple audio sources into
   *      another Amplitude + Pi computation (circle).
   *          An algorithm similar to Ray Marching may work. By having
   *      different audio groups act as ,,circles'' with their own audio/
   *          buffer sources and their own angles. ---- We can further treat
   *      these with a Command design pattern and an Input Handler from
   *          the controller classes.
   */
  
  alcMakeContextCurrent(NULL);
  alcDestroyContext(deviceConfig->alcContext);
  alcCloseDevice(deviceConfig->alcDevice);
  
  alDeleteSources(1, &uSource);
  alDeleteBuffers(1, &alUBuffer);
}

ALdouble
AudioFrameProcessor::ProcessAudioSample(std::array<double, 0xFF> &inputSamples) {
  auto xn = 0.0;
  auto biquad = new BiquadFilter();
  auto state = new BiquadState();
  for (auto i = 0; i < deviceConfig->soundInfo->channels; i++) {
    xn = inputSamples.at(i);
    double processor = biquad->input_coefficient_a0 * xn *
      state->audio_channel_buffer_male_input +
      biquad->input_coefficient_a1 *
      state->audio_channel_buffer_female_input +
      biquad->output_coefficient_b1 *
      state->audio_channel_buffer_male_output +
      biquad->output_coefficient_c0 *
      state->audio_channel_buffer_female_output;
    
    DenormalizeDiscreteValue(processor, 1);
    DenormalizeDiscreteValue(processor, -1);
    
    state->audio_channel_buffer_female_input =
      state->audio_channel_buffer_male_input;
    state->audio_channel_buffer_male_input = xn;
    state->audio_channel_buffer_female_output =
      state->audio_channel_buffer_male_output;
    state->audio_channel_buffer_male_output = processor;
    
    inputSamples.at(i) = processor;
  }
  
  return xn;
}

ALdouble AudioFrameProcessor::ProcessAudioSample(double xn) {
  auto deviceConfig = new AudioInterface::DeviceConfig;
  AudioFrameProcessor::ConfigureDevice(deviceConfig);
  
  // TODO(Daniel): JSON with JSON-CPP or parsing with a .conf file(?)
  SNDFILE *soundFiles = sf_open("/public/resource/audio/sample-base.ogg", 0,
                                deviceConfig->soundInfo);
  LoadItems(deviceConfig->soundInfo); // or a process my dude
  
  xn = deviceConfig->soundInfo->samplerate;
  std::array<double, 0xFF> samples;
  samples.fill(xn);
  
  this->ProcessSampleSet(samples); // recursive i/o-state-handler
  return xn;
}