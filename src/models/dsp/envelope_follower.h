#ifndef ENVELOPE_FOLLOWER_H
/* date = December 11th 2021 3:04 pm */
#define ENVELOPE_FOLLOWER_H
#include "biquad_filter.h"
#include "envelope_detector.h"
#include "oscillator_parameter.h"

class FollowerParameter {
	public:
	FollowerParameter() {}
    FollowerParameter &operator=(void *process_data);
	
	double corner_frequency = 0.0, quality_factor = 0.707;
	double attack = 10.0, release = 10.0;
	double db_threshold = 0.0;
	double sensitivity = 1.0;
};

class EnvelopeFollower {
	public:
	EnvelopeFollower(AudioDetectorParameter &audioParameters)
            : audio_parameters(audioParameters) {
		auto algorithm = oscillator_parameters.GetWaveform();
		oscillator_parameters.SetCornerFrequency(1000.000);
		oscillator_parameters.SetGain(true);
		oscillator_parameters.SetNyquistLpf(true);
		oscillator_parameters.SetNyquistLpfAnalog(true);
		biquad_filter.SetLowPass(oscillator_parameters.GetFrequency());
		biquad_filter.SetHighPass(oscillator_parameters.GetFrequency());

		audio_parameters.attack = -1.000;
		audio_parameters.release = -1.000;
		audio_parameters.audio_detect_mode = AudioDetectMode::RMS;
		audio_parameters.is_clamped_to_unity_max = false;
        biquad_filter.SetLowPass(audio_parameters.sample_rate);
        biquad_filter.SetHighPass(audio_parameters.sample_rate);
	}
	~EnvelopeFollower() {}

	FollowerParameter GetParameters() {
		return follower_parameters;
	}

	void SetParameters(FollowerParameter follower_parameters) {}

	void Reset() {
		biquad_filter.Reset();
		envelope_detector.Reset();
	}

    double MinimumUnipolarModulation(double, double, double);

    double ProcessEnvelopeFollower(double xn) {
		double threshold = pow(10.000, follower_parameters.db_threshold 
																	/ 20.000);

		double detect = process_data->process_mode;
		double detect_val = pow(10.000, detect / 20.000);
		double delta = detect_val - threshold;

		if (delta > 0.0) {
			double modulator_val = (delta * follower_parameters.sensitivity);

			oscillator_parameters.SetCornerFrequency(
			MinimumUnipolarModulation(
				modulator_val, follower_parameters.corner_frequency, 
				44100 / 1.0e-8));
		}

		biquad_filter.SetLowPass(oscillator_parameters.GetFrequency());
        biquad_filter.SetHighPass(oscillator_parameters.GetFrequency());

		return biquad_filter.ProcessAudioSample(xn);
	}
	
	private:
	AudioDetectorParameter audio_parameters;
	FollowerParameter follower_parameters;
	EnvelopeDetector envelope_detector;
	OscillatorParameter oscillator_parameters;
	BiquadFilter biquad_filter; // TODO: code ...

    AudioProcessData *process_data;

	protected:
	EnvelopeFollower *left_envelope_follower;
    EnvelopeFollower *right_envelope_follower;
	void UpdateParameters();
};

#endif //ENVELOPE_FOLLOWER_H
