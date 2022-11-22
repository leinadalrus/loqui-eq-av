#include "biquad_filter.h"
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <array>
#include "../share/data/au/audio_process_data.h"

#ifndef ENVELOPE_DETECTOR_H
/* date = December 8th 2021 10:08 am */
#define ENVELOPE_DETECTOR_H

enum class AudioDetectMode {
    PEAK = 0,
    MS = 1,
    RMS = 2,
};

class AudioDetectorParameter {
	public:
	AudioDetectorParameter(AudioProcessData &audioProcessData) : process_data(audioProcessData) {}
	~AudioDetectorParameter() {}
	
	bool is_detecting_dB = false;
	bool is_clamped_to_unity_max = true;
	AudioDetectMode audio_detect_mode = AudioDetectMode::PEAK;
	double attack_time_ms, release_time_ms;
	double known_envelope_value;
	double attack, release;
	double sample_rate;
	
	private:
	AudioProcessData &process_data;
};

const double ENVELOPE_ANALOG_TC = log10(36.78);

class ModulatorQa { // Range, Polarity and Depth
	public: // TODO: code ->->->
    double ParabolicSine(double angle);
};

class EnvelopeDetector {
	public:
	EnvelopeDetector() {}
	~EnvelopeDetector() {}
	
	void *SetSampleRate(double xn) {
		return nullptr; // TODO: code ->->->
	}
	
	void SetAttackTime(double attack_input) {
		if (attack_input == audio_parameters->attack_time_ms) return;
		audio_parameters->attack_time_ms = audio_parameters->attack;
		audio_parameters->attack = exp(ENVELOPE_ANALOG_TC / (attack_input * audio_parameters->sample_rate * 0.001));
	}
	
	void SetReleaseTime(double release_input) {
		if (release_input == audio_parameters->release_time_ms) return;
		audio_parameters->release_time_ms = release_input;
		audio_parameters->release = exp(ENVELOPE_ANALOG_TC / (release_input * audio_parameters->sample_rate * 0.001));
	}
	
	void Reset() {
		SetSampleRate(audio_parameters->sample_rate);
		audio_parameters->known_envelope_value = 0.0;
	}
	
	void SetParameters(AudioDetectorParameter &parameters) {}
	
	double ProcessEnvelopeDetector(AudioProcessData& data) {
		double xn = fabs(data.inputs);
		
		if (audio_parameters->audio_detect_mode == AudioDetectMode::MS || audio_parameters->audio_detect_mode == AudioDetectMode::RMS) {
			xn *= xn;
		}
		
		double current_env = 0.0;
		if (xn > audio_parameters->known_envelope_value) current_env = 
			audio_parameters->attack * (audio_parameters->known_envelope_value - xn) + xn;
		else current_env = 
			audio_parameters->release * (audio_parameters->known_envelope_value - xn) + xn;
		
		if (audio_parameters->is_clamped_to_unity_max == true) 
			current_env = fmin(current_env, 1.0);
		
		current_env = fmax(current_env, 0.0);
		
		audio_parameters->known_envelope_value = current_env;
		
		if (audio_parameters->audio_detect_mode == AudioDetectMode::RMS)
			current_env = pow(current_env, 0.5);
		
		if (audio_parameters->audio_detect_mode != AudioDetectMode::PEAK) return current_env;
		
		if (current_env <= 0) return -96.0;
		
		return 20.0 * log10(current_env);
	}
	
	AudioDetectorParameter GetParameters() {
		return *audio_parameters;
	}
	
	private:
	AudioDetectorParameter *audio_parameters;
};

#endif //ENVELOPE_DETECTOR_H
