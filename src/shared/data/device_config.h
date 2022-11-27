#include "../../../lib/libsndfile/include/sndfile.h"
#include "../../../lib/openalsoft/include/AL/alext.h"
#include "../../../lib/openalsoft/include/AL/alc.h"
#include "../../../lib/openalsoft/include/AL/al.h"

#include <cstdlib>
#include <cstdio>
#include <memory>

#ifndef C9B714D5_E6E0_443A_A7A2_52904655CC74
#define C9B714D5_E6E0_443A_A7A2_52904655CC74

namespace AudioInterface {

class DeviceConfig {
public:
    ALCdevice *alcDevice;
    ALCcontext *alcContext;
    LPALCGETSTRINGISOFT alcGetStringiSOFT;
    LPALCRESETDEVICESOFT alcResetDeviceSOFT;

    SF_INFO *soundInfo;
    int sampleSize;
private: // (?)
};

class SoundManager {
public:
    SNDFILE *sndfile;
    SF_INFO *sfInfo;
};

class DeviceIDLoader {
public:
    void LoadDeviceReset(ALCdevice *alcDevice,
                     LPALCRESETDEVICESOFT alcResetDeviceSOFTA,
                     LPALCRESETDEVICESOFT alcResetDeviceSOFTB);

    void LoadStringGetter(ALCdevice *alcDevice,
                      LPALCGETSTRINGISOFT alcGetStringiSOFTA,
                      LPALCGETSTRINGISOFT alcGetStringiSOFTB);
};

} // namespace AudioInterface


#endif /* C9B714D5_E6E0_443A_A7A2_52904655CC74 */
