#include "../biquad.h"
#include "../../../lib/SDL2/include/SDL2/SDL.h"

#ifndef BF067CAF_893E_42E6_B573_8AC8769AFFA8
#define BF067CAF_893E_42E6_B573_8AC8769AFFA8

class Observer {
public:
    Observer() {}
    ~Observer() {}
    void OnEvent(BiquadFilter *biquad, SDL_AudioDeviceEvent event);
};

#endif /* BF067CAF_893E_42E6_B573_8AC8769AFFA8 */
