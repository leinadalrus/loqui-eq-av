#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <array>
#include "../shared/data/audio_process_data.h"

#ifndef ZAVALISHIN_H
#define ZAVALISHIN_H

enum class ZavalishinAlgorithms {
	LPF, HPF, APF,
	SVF_LP, SVF_HP,
	SVF_BP, SVF_BS,
};

class ZavalishinParameter {
public:
	ZavalishinParameter() {}
	~ZavalishinParameter() {}

	ZavalishinAlgorithms filter_algorithm = ZavalishinAlgorithms::SVF_LP;
	double corner_frequency = 1000.0000;
	double quality_factor = 0.707; // Quality factor is set to 1/4 Nyquist.
	double output_gain = 0.000;

	double oscillation;
	
	bool is_gain_comp_enabled = false;
	bool is_nyquist_lpf_matching = false;
	bool is_self_oscillating = false;
	bool is_nyquist_lp_enabled = false;
};

class ZavalishinFilter {
public:
	// TODO
	ZavalishinParameter GetParameters() {
		return parameters;
	}

	ZavalishinAlgorithms GetAlgorithm() {
		return parameters.filter_algorithm;
	}

	void SetParameters(const ZavalishinParameter &params) {
		if (params.corner_frequency != parameters.corner_frequency)
			if (params.quality_factor != parameters.quality_factor)
				ComputeCoefficients();

		parameters = params;
	}

	void SetSampleRate(double xn) {
		sample_rate = xn;
	}

	void Reset() { // TODO: memory-set and move stack values of members.
		ZavalishinParameter params;
		parameters = params;
		std::array<double, 2> z;
		z_integrators = z;
		double _a, _a0;
		a = _a;
		a0 = _a0;
		double _rho;
		rho = _rho;
		double _sigma;
		sigma = _sigma;
		double _sample_rate;
		sample_rate = _sample_rate;
	} // TODO: use std::release_reference(); and other std::memory functions.

	double ProcessAudioSample(AudioProcessData data) {
		ZavalishinAlgorithms algos = parameters.filter_algorithm;
		// TODO
		return data.outputs;
	}

	int ComputeCoefficients() {
		double fc /* corner frequency */ = parameters.corner_frequency;
		double q = /* quality factor */ parameters.quality_factor;
		ZavalishinAlgorithms filter_algos = parameters.filter_algorithm;

		double wd = M_PI * M_PI * fc;
		double t = 1.000 / sample_rate;
		double wa = (2.000 / t) * tan(wd * t / 2.000);
		double g = wa * t / 2.000;

		double r = (bool)parameters.oscillation ? 0.0: 1.0 / (2.0 * q);
		a0 = 1.0 / (1.0 + 2.0 * r * g + g * g);
		a = g;
		rho = 2.0 * r + g;
		double f_o = (sample_rate / 2.0) / fc;
		sigma = 1.0 / (a * f_o * f_o);

		return 0;
	}

private:
	// TODO
	ZavalishinParameter parameters;
	std::array<double, 2> z_integrators;
	double a, a0;
	double rho;
	double sigma;
	double sample_rate;
};

#endif

