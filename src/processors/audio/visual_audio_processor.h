#ifndef VISUAL_AUDIO_PROCESSOR_H
#define VISUAL_AUDIO_PROCESSOR_H

#include <condition_variable>
#include <functional>
#include <algorithm>
#include <iostream>
#include <utility>
#include <iomanip>
#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <atomic>
#include <cerrno>
#include <chrono>
#include <cstdio>
#include <future>
#include <memory>
#include <string>
#include <thread>
#include <vector>
#include <array>
#include <cmath>
#include <deque>
#include <mutex>
#include <ratio>

class VisualAudioProcessor {
public:
  void frameCallback(plm_t *plm, plm_frame_t *frame, void *data);

  void audioCallback(plm_t *plm, plm_frame_t *frame, void *data);

  int processCallbacks(plm_t *plm);
};


#endif // VISUAL_AUDIO_PROCESSOR_H