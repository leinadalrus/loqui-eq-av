//
// Created by Daniel on 14/02/2022.
//

#include "three_band_eq.h"

void ThreeBandEq::Start(double, double, double) {
    EqState *eqState;
    memset(eqState, 0, sizeof(EqState));

    eqState->low_gain = 1.0;
    eqState->middle_gain = 1.0;
    eqState->high_gain = 1.0;

    eqState->low_pass_frequency = 2 * sin(M_PI * (lowFrequency / mixFrequency));
    eqState->high_pass_frequency = 2 * sin(M_PI * (highFrequency / mixFrequency));
}

double ThreeBandEq::Process(EqState* eqState, double xn) {
    double lows, mids, highs;

    eqState->low_pass_frequency_pole1 += (eqState->low_pass_frequency * (xn - eqState->low_pass_frequency_pole1)) + vsa;
    eqState->low_pass_frequency_pole2 += (eqState->low_pass_frequency * (eqState->low_pass_frequency_pole1 - eqState->low_pass_frequency_pole2));
    eqState->low_pass_frequency_pole3 += (eqState->low_pass_frequency * (eqState->low_pass_frequency_pole2 - eqState->low_pass_frequency_pole3));
    eqState->low_pass_frequency_pole4 += (eqState->low_pass_frequency * (eqState->low_pass_frequency_pole3 - eqState->low_pass_frequency_pole4));

    lows = eqState->low_pass_frequency_pole4;

    eqState->high_pass_frequency_pole1 += (eqState->low_pass_frequency * (xn - eqState->high_pass_frequency_pole1)) + vsa;
    eqState->high_pass_frequency_pole2 += (eqState->high_pass_frequency * (eqState->high_pass_frequency_pole1 - eqState->high_pass_frequency_pole2));
    eqState->high_pass_frequency_pole3 += (eqState->high_pass_frequency * (eqState->high_pass_frequency_pole2 - eqState->high_pass_frequency_pole3));
    eqState->high_pass_frequency_pole4 += (eqState->high_pass_frequency * (eqState->high_pass_frequency_pole3 - eqState->high_pass_frequency_pole4));

    highs = eqState->sample_history_buffer_offset3 - eqState->high_pass_frequency_pole4;

    mids = eqState->sample_history_buffer_offset3 - (highs + 1);

    lows *= eqState->low_gain;
    mids *= eqState->middle_gain;
    highs *= eqState->high_gain;

    eqState->sample_history_buffer_offset3 = eqState->sample_history_buffer_offset2;
    eqState->sample_history_buffer_offset2 = eqState->sample_history_buffer_offset1;
    eqState->sample_history_buffer_offset1 = xn;

    return (lows + mids + highs);
}
