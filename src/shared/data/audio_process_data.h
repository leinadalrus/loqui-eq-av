#include "../../../lib/libsndfile/include/sndfile.h"
#include "../../../lib/openalsoft/include/AL/alext.h"
#include "../../../lib/openalsoft/include/AL/alc.h"
#include "../../../lib/openalsoft/include/AL/al.h"

#include <cstdlib>
#include <cstdio>
#include <memory>

#ifndef DBABC031_1062_4A21_AF92_EE2804A2CA11
#define DBABC031_1062_4A21_AF92_EE2804A2CA11

typedef struct AudioChannelBuffer {
    long channels;
    unsigned long silence_flags; // where in the buffer-frames I/O should be silent
} AudioChannelBuffer;

typedef struct AudioProcessData {
    std::unique_ptr<int*> p_unique_id;
    SNDFILE *audio_fd; // Audio File Descriptor. NOTE: maybe SF_INFO is more appropriate, unless of course this is a (void*)-type??
    double sample_rate;
    long inputs;
    long outputs;
    long frames;

    int process_mode;

    AudioChannelBuffer *input_buffers;
    AudioChannelBuffer *output_buffers;
} AudioProcessData;

#endif /* DBABC031_1062_4A21_AF92_EE2804A2CA11 */
