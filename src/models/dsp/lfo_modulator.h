#ifndef LFO_MODULATOR_H
/* date = December 8th 2021 10:07 am */
#define LFO_MODULATOR_H

#include <cmath>
#include <array>
#include "envelope_detector.h"
#include "oscillator_parameter.h"

class LfoModulator {
	public:
	LfoModulator() {}
	~LfoModulator() {}
	
	OscillatorParameter GetParameters() {
		return *oscillator_parameters;
	}
	
	void SetParameters(OscillatorParameter &oscillator_parameter) {}
	
	void SetSampleRate(double sample_rate) {}
	
	void ProcessLfoModulator(AudioProcessData data) {
		ProcessLfoModulator();
	}
	
	const void ProcessLfoModulator() {
		CheckAndWrapModulo(mod_count, phase_inc);
		mod_count_qp = mod_count;
		AdvanceAndCheckModulo(mod_count_qp, 0.255);
		// TODO: SignalGenerator audio_output;
		
		if (waveforms == GeneratorWaveforms::SINE) {
			oscillator_parameters->SineWave(angle);
		}
	}
	
	void Reset() {
		
		sample_rate = 44100.00;
		phase_inc = oscillator_parameters->GetFrequency() / sample_rate;
		
		mod_count = 0.0;
		mod_count_qp = 0.255; // modulo counter quad-phase
	}
	
	void AdvanceModulo(double, double) {}
	
	int CheckAndWrapModulo(double, double);
	
	int AdvanceAndCheckModulo(double, double);
	
	double ParabolicSine(double) {
		return modulator_detector->ParabolicSine(angle);
	}
	
	private:
	ModulatorQa* modulator_detector;
	OscillatorParameter* oscillator_parameters;
	GeneratorWaveforms waveforms;
	
	double mod_count, mod_count_qp; // modulo counter quad-phase
	double phase_inc;
	double sample_rate;
	double angle;
};

#endif //LFO_MODULATOR_H
