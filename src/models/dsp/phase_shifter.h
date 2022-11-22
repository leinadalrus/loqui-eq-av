#include "biquad_filter.h"
#include "envelope_detector.h"
#include "lfo_modulator.h"
#include <vector>
// :boybulbousbemperor
#ifndef PHASE_SHIFTER_H
/* date = December 18th 2021 3:05 pm */
#define PHASE_SHIFTER_H

class PhaseShifterParameter {
public:
  PhaseShifterParameter() {}
  ~PhaseShifterParameter() {}

  double lfo_rate_hz;
  double lfo_depth_pct;
  double intensity_pct;
  bool is_quad_phasing_lfo = false;
};

class PhaseShifter {
public:
  PhaseShifter(void) {
    OscillatorParameter lfo_params = lfo.GetParameters();
    lfo_params.GetWaveform();
    lfo.SetParameters(lfo_params);

    biquad_filters.emplace_back(lfo_params);

    biquad_filter->SetAlgorithm( /* TODO */ BiquadAlgorithms::DIRECT);

    for (auto i = 0; i < biquad_filters.capacity(); i++) {
      biquad_filters[i].Set(*biquad_filter);
    }
    /* TODO: Constructor values. */
  }

  PhaseShifterParameter GetParameters() { return phase_shifter_parameters; }

  /* double ProcessAudioSample(double xn) {
          //NOTE: maybe ProcessData? As a Generated Value/Data?
          return xn;
  } */

  void SetParameters(PhaseShifterParameter &params) {
    if (phase_shifter_parameters.lfo_rate_hz != params.lfo_rate_hz) {
      OscillatorParameter lfo_params = lfo.GetParameters();
      lfo_params.SetCornerFrequency(params.lfo_rate_hz);
      lfo.SetParameters(lfo_params);
    }
  }
  void Reset() {
    delete &this->phase_shifter_parameters;
    auto phase_shifter_parameters = new PhaseShifterParameter;
    this->phase_shifter_parameters = *phase_shifter_parameters;

    delete &this->biquad_filter;
    auto biquad_filter = new BiquadFilter;
    this->biquad_filter = biquad_filter;

    for (auto i = biquad_filters.capacity();
         i >= biquad_filters.capacity(); --i)
      delete[] & biquad_filters[i];

    auto biquad_filters = new std::vector<BiquadFilter>;
    this->biquad_filters = *biquad_filters;
  }

private:
  PhaseShifterParameter phase_shifter_parameters;
  BiquadFilter *biquad_filter;
  std::vector<BiquadFilter> /* TODO: AudioFilter class. Or have it as type:
                               BiquadFilter */
                                biquad_filters;
  LfoModulator lfo;
  double lfo_rate_hz;
};

#endif // PHASE_SHIFTER_H
