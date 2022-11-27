#include <corecrt_math.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>

double NormalizeDiscreteValue(double discrete_value, int step_count) {
    double normalized = discrete_value / (double) step_count;
    return normalized;
}

int DenormalizeDiscreteValue(double discrete_value, int step_count) {
    double normalized_value = NormalizeDiscreteValue(discrete_value, step_count);
    discrete_value = fmin(step_count, normalized_value * (step_count + 1));
    return (int)discrete_value;
}

//
// Created by 'Boy Bulbous BEmperor' on 12/02/2022.
//
