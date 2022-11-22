#include "waveshaper.h"
#include "biquad_filter.h"

#ifndef TRIODE_CLASS_A
#define TRIODE_CLASS_A

class TriodeClassAParameter {
public:
	Waveshapes distortion_type = Waveshapes::SOFT_CLIP;
	double saturation = 1.000;
	double asymmetry = 0.000;
	double output_gain = 1.000;
	bool is_output_inverted = true;
	bool is_hpf_enabled = true;
	bool is_lpf_enabled = false;
	double hpf_corner_frequency = 1.000;
	double lsf_fshelf = 80.000;
	double lsf_boostcut_db = 0.000;
};

class TriodeClassA {
public:
	TriodeClassA() {
		BiquadFilter biquad;
		auto filter = biquad.Get();
		filter.SetFrequency(triode_class_a_parameters.hpf_corner_frequency);
		hpf_output.Set(filter);

		auto algorithm = biquad.GetAlgorithm();
		*algorithm = BiquadAlgorithms::DIRECT;
		
		auto parameters = biquad.Get();
		parameters.SetFrequency(triode_class_a_parameters.lsf_boostcut_db);
		lpf_output.Set(parameters);
	}
	
	TriodeClassAParameter GetParameters() {
		return triode_class_a_parameters;
	}

	void SetParameters(BiquadFilter /* NOTE: or BiquadFilter */ &filter){}

	void Reset() { /* TODO */ }

	double ProcessAudioSample(AudioProcessData data) {
		return data.outputs;
	}

private:
	// TODO
	TriodeClassAParameter triode_class_a_parameters;
	BiquadFilter hpf_output;
	BiquadFilter lpf_output;

};

#endif

