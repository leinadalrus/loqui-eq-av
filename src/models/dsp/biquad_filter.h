#include <array>
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include "../shared/data/audio_process_data.h"
#include <array>


#ifndef BIQUAD_FILTER_H
#define BIQUAD_FILTER_H

const double CNST_VAL_PI = 3.14159;
// Enumerated-types
enum class BiquadAlgorithms {
  DIRECT,
  CANONICAL,
  TRANSPOSE_DIRECT,
  TRANSPOSE_CANONICAL,
};

enum class FilterCoefficients {
  A0,
  A1,
  A2,
  B1,
  B2,
  C0,
  D0,
  N,
};

enum class StatesCoefficients {
  INPUT_COEFFICIENT_A0,
  INPUT_COEFFICIENT_A1,
  INPUT_COEFFICIENT_B0,
  OUTPUT_COEFFICIENT_B1,
  OUTPUT_COEFFICIENT_C0,
};

// Biquad Filter
class BiquadState {
public:
  double audio_channel_buffer_male_input = 0.000;
  double audio_channel_buffer_female_input = 0.000;
  double audio_channel_buffer_male_output = 0.000;
  double audio_channel_buffer_female_output = 0.000;
};

class BiquadFilter {
public:
  /*  void Resize() {
  for (auto channel_index = 0; channel_index < states.size(); ++channel_index) {
                  // states.sizeof() should be channelsCount but eh meh
          for (auto sample_index = 0; sample_index < states.size();
++sample_index) {
                  // TODO

          }
  }
} */

  void SetAlgorithm(BiquadAlgorithms);
  BiquadAlgorithms *GetAlgorithm();
  void SetFrequency(double);
  double GetFrequency();
  void Set(BiquadFilter);
  BiquadFilter Get();

  void Reset() {
    for (auto i = 0; i < states.size(); ++i) {
      BiquadState channel_state = states[i];
      channel_state.audio_channel_buffer_male_input = 0;
      channel_state.audio_channel_buffer_male_output = 0;
      channel_state.audio_channel_buffer_female_input = 0;
      channel_state.audio_channel_buffer_female_output = 0;
    }
  }

  void LowPass(double xn) {
    const double a = sin(xn) * sqrt(2.0) / 2.0; // square-root 2 against 2
    const double cosine_0 = cos(xn);

    const double b0 = (1 - cosine_0) * 0.5;
    const double b1 = 1 - cosine_0;
    const double b2 = (1 - cosine_0) * 0.5;

    const double inverse_a = 1 / (1 + a); // quality-factor
    const double a1 = -2 * cosine_0;
    const double a2 = 1 - a;

    input_coefficient_a0 = b0 * inverse_a;
    input_coefficient_a1 = b1 * inverse_a;
    input_coefficient_b0 = b2 * inverse_a;

    output_coefficient_b1 = a1 * inverse_a;
    output_coefficient_c0 = a2 * inverse_a;
  }

  void SetLowPass(double sampling) {
    double frequency = sin(sampling) * sqrt(2.0) /
                       2.0; // sinusoidal frequency of sample; kills-self if at
                            // the same frequency and amplitude.
    double cutoff =
        cutoff * cos(frequency) *
        CNST_VAL_PI; // cosine frequency of sample, times into itself so that it
                     // cuts the high-pass frequencies and only emits low-pass
                     // frequencies;

    double quality_factor =
        1.0 / (cutoff + frequency); // quality-factor := 1 / w

    input_coefficient_a0 = output_coefficient_b1 =
        frequency * quality_factor; // stereo inputs - audio channel bufferings
    input_coefficient_a1 = (frequency - cutoff) * quality_factor;
  }

  void HighPass(double xn) {
    const double a = sin(xn) * sqrt(2.0) / 2.0;
    const double cosine_0 = cos(xn);

    const double b0 = (1 + cosine_0) * 0.5;
    const double b1 = -(1 + cosine_0);
    const double b2 = (1 + cosine_0) * 0.5;

    const double inverse_a = 1 / (1 + a);
    const double a1 = -2 * cosine_0;
    const double a2 = 1 - a;

    input_coefficient_a0 = b0 * inverse_a;
    input_coefficient_a1 = b1 * inverse_a;
    input_coefficient_b0 = b2 * inverse_a;

    output_coefficient_b1 = -a1 * inverse_a;
    output_coefficient_c0 = -a2 * inverse_a;
  }

  void SetHighPass(double sampling) {
    double frequency = 2.0 * sampling;
    double quality_factor = 1.000000 / (cutoff + frequency);
    input_coefficient_a0 = frequency * quality_factor;
    input_coefficient_a1 = -input_coefficient_a0; // inverse-alpha value
    output_coefficient_b1 = (frequency - cutoff) * quality_factor;
  }

  void LowPassResonant(double xn, double quality_factor) {
    const double a = sin(xn) / (quality_factor * 2);
    const double cosine_0 = cos(xn);

    const double b0 = (1 - cosine_0) * 0.5;
    const double b1 = 1 - cosine_0;
    const double b2 = (1 - cosine_0) * 0.5;

    const double inverse_a = 1 / (1 + a);
    const double a1 = -2 * cosine_0;
    const double a2 = 1 - a;

    input_coefficient_a0 = b0 * inverse_a;
    input_coefficient_a1 = b1 * inverse_a;
    input_coefficient_b0 = b2 * inverse_a;

    output_coefficient_b1 = -a1 * inverse_a;
    output_coefficient_c0 = -a2 * inverse_a;
  }

  void HighPassResonant(double xn, double quality_factor) {
    const double a = sin(xn) / (quality_factor * 2);
    const double cosine_0 = cos(xn);

    const double b0 = (1 - cosine_0) * 0.5;
    const double b1 = -(1 - cosine_0);
    const double b2 = (1 - cosine_0) * 0.5;

    const double inverse_a = 1 / (1 + a);
    const double a1 = -2 * cosine_0;
    const double a2 = 1 - a;

    input_coefficient_a0 = b0 * inverse_a;
    input_coefficient_a1 = b1 * inverse_a;
    input_coefficient_b0 = b2 * inverse_a;

    output_coefficient_b1 = -a1 * inverse_a;
    output_coefficient_c0 = -a2 * inverse_a;
  }

  double ProcessAudioSample(double xn);

  double input_coefficient_a0 = 0;
  double input_coefficient_a1 = 0;
  double input_coefficient_b0 = 0;

  double output_coefficient_b1 = 0;
  double output_coefficient_c0 = 0;

private:
  BiquadFilter &operator=(const BiquadFilter &);
  BiquadAlgorithms biquad_algorithm = BiquadAlgorithms::DIRECT;
  std::array<FilterCoefficients, 8> filter_coefficients;
  std::array<BiquadState, 8> states;

  double cutoff;
  double corner_frequency; // Equals whatever frequency depending on input.
  double quality_factor = 0.707; // 1/4 Nyquist
};

#endif // BIQUAD_FILTER_H