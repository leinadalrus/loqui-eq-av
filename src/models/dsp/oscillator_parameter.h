#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <array>
#include "../share/data/au/audio_process_data.h"
#include "generator_waveforms.h"

#ifndef EFE3BA66_A836_4FBA_AF8D_A57384BDE529
#define EFE3BA66_A836_4FBA_AF8D_A57384BDE529

class OscillatorParameter {
public:
	OscillatorParameter() {}
	~OscillatorParameter() {}
	
	void SineWave(double angle) {
        angle = mod_count * 2.00 * M_PI - M_PI;
		/* process_data->outputs = */ ParabolicSine(-angle);
//		angle = mod_count_qp * 2->00 * CNST_VAL_PI - CNST_VAL_PI;
//		process_data->quad_phase_position = ParabolicSine(-angle); TODO: change to another type and value->
	}
	
	void SawWave(double angle) {} // TODO
	
	void TriangleWave(double angle) {} // TODO

    double ParabolicSine(double angle) {
        return audio_process_data->outputs;
    }

	double GetFrequency() {
		return frequency;
	}

	GeneratorWaveforms GetWaveform() {
		return waveform;
	}

	void SetCornerFrequency(double frequency) {
		this->frequency = frequency;
	}
	
	void SetGain(bool is_gain) {
		this->is_gain = is_gain;
	}

	void SetNyquistLpf(bool is_nyquist_lpf) {
		this->is_nyquist_lpf = is_nyquist_lpf;
	}

	void SetNyquistLpfAnalog(bool is_nyquist_lpf_analog) {
		this->is_nyquist_lpf_analog = is_nyquist_lpf_analog;
	}
	
private:
    AudioProcessData *audio_process_data;
	GeneratorWaveforms waveform = GeneratorWaveforms::SINE;
	double frequency = 0.0;
    double mod_count;

	bool is_gain = false;
	bool is_nyquist_lpf = false;
	bool is_nyquist_lpf_analog = false;
};

#endif /* EFE3BA66_A836_4FBA_AF8D_A57384BDE529 */
