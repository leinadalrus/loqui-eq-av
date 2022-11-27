/* date = March 20th 2022 11:49 am */

#ifndef AUDIO_DATA_TYPES_H
#define AUDIO_DATA_TYPES_H

class AudioDataTypes {
    public:
    enum class AudioFileTypes {
        PCM = 0,
        MP3 = 1,
        AAC = 2,
        OGG = 3,
        FLAC = 4,
        ALAC = 5,
        WAV = 6,
        AIFF = 7,
    };
};

#endif //AUDIO_DATA_TYPES_H
