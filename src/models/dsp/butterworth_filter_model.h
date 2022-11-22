#include "biquad_filter.h"

#ifndef BUTTERWORTH_FILTER_H
#define BUTTERWORTH_FILTER_H

class ButterworthFiter: public BiquadFilter {
public:
  ButterworthFilter(BiquadFilter *biquad): biquadFilter(biquad) {}
  
private:
  BiquadFilter *biquadFilter = BiquadFilter::onload();
  
};

#endif // BUTTERWORTH_FILTER_H