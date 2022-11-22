#include "biquad_filter.h"

BiquadAlgorithms *BiquadFilter::GetAlgorithm() {
    return &biquad_algorithm;
}