//
// Created by Daniel on 14/02/2022.
//
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>

#define _USE_MATH_DEFINES
#define M_PI 3.14159265358979323846

#ifndef WYND_THREE_BAND_EQ_H
#define WYND_THREE_BAND_EQ_H

class EqState {
public:
    double low_pass_frequency;
    double low_pass_frequency_pole1; // initial pole value
    double low_pass_frequency_pole2; // pole value for low-pass/low gain frequencies
    double low_pass_frequency_pole3; // middle frequency pole value
    double low_pass_frequency_pole4; // high frequency pole value

    double high_pass_frequency;
    double high_pass_frequency_pole1; // initial destination pole value
    double high_pass_frequency_pole2; // low frequency pole value's destination
    double high_pass_frequency_pole3;
    double high_pass_frequency_pole4;

    double sample_history_buffer_offset1; // offset buffers for turning values from continuous to discrete
    double sample_history_buffer_offset2;
    double sample_history_buffer_offset3;

    double low_gain; // should be self-explanatory
    double middle_gain;
    double high_gain;
};

class ThreeBandEq {
public:
    EqState eqState;
    double const vsa = (1.0 / 4294967295.0);
    double xn;

    void Start(double, double, double);
    double Process(EqState* eqState, double xn);

private:
    double lowFrequency, highFrequency, mixFrequency;
}; // C Neil, 2006-08-29 20:34:25, "3 Band Equaliser", Available [online]: https://www.musicdsp.org/en/latest/Filters/236-3-band-equaliser.html

#endif //WYND_THREE_BAND_EQ_H
