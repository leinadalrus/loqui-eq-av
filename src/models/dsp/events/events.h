#include "../../../lib/SDL2/include/SDL2/SDL.h"

#ifndef B3E3BC61_C135_42CB_B607_65FECD78FEEF
#define B3E3BC61_C135_42CB_B607_65FECD78FEEF

typedef struct AbstrEvents { // Abstract Events
    // void-pointer types shouldn't be your convention for coding, but this
        // is a like m best way to manage event data through abstraction
    void*data{0}; // static_cast or reinterpret_cast this when used
} AbstrEvents;

class UserEvents: public SDL_AudioDeviceEvent {
public:
    UserEvents() = default; // shouldn't use default, but its only one member so
        // ... yeah ...
    SDL_AudioDeviceEvent getAudioDeviceEvents() {
        return audioDeviceEvents;
    }
private:
    AbstrEvents abstractEvents;
    SDL_AudioDeviceEvent audioDeviceEvents;
};

#endif /* B3E3BC61_C135_42CB_B607_65FECD78FEEF */
