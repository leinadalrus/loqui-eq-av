#include "../../../lib/openalsoft/include/AL/al.h"

#ifndef HRTF_PROCESS_DATA_H
/* date = March 18th 2022 0:32 pm */
#define HRTF_PROCESS_DATA_H

// Head-related Transfer
class HrtfProcessData {
    public:
    ALdouble yPolePosition;
    ALdouble xPolePosition;
    ALdouble angle;
    private:
};

#endif //HRTF_PROCESS_DATA_H
