#include "biquad_filter.h"

#ifndef TWO_BAND_SHELF_H
#define TWO_BAND_SHELF_H

class TwoBandState {
public:
	double low_pass_frequency; // Low Band
	double lpf_n0, lpf_n1, lpf_n2, lpf_n3;
	// High Band
	double high_pass_frequency;
	double hpf_n0, hpf_n1, hpf_n2, hpf_n3;
	// Sample value - (minus) `x`.
	double sample_vs1, sample_vs2, sample_vs3;

	double gain; // Probably have multiple instances of?!

	void InitializeTwoBands(double lpf, double hpf);
	double ProcessTwoBands(double xn);
};

class TwoBandShelfParameter {
public:
	TwoBandShelfParameter() {}
	~TwoBandShelfParameter() {}

	double low_shelf_fc = 0.000, // i.e corner_frequency
		low_shelf_db = 0.000;  // i.e gain_boost_cut_db

	double high_shelf_fc = 0.000, // i.e corner_frequency
		high_shelf_db = 0.000; // i.e gain_boost_cut_db
};

class TwoBandShelf {
public:
	double SetShelvingLow(AudioProcessData data) {
		const double a = sin(data.inputs) / (quality_factor * 2);
		const double s = s * log(10) / 40 * sin(two_band_state.lpf_n0) / two_band_state.lpf_n0 * (a/* ^2 */- 1);

		double theta = 2 * M_PI * corner_frequency / s;
		double mu = 10 * gain_boostcut_db / 20;
		double beta = 4 / (1 + mu);
		double bt = beta * tan(theta / 2);
		double dyn = (1 - bt) /  (1 + bt);

		double a0 = (1 - dyn) / 2;
		double a1 = (1 - dyn) / 2;

		double b1 = -dyn;
		double b2 = 0.000;

		double c0 = mu - 10;
		
		double d0 = 1.000;
		double sdxn = 1 / (/* s^2- */ s / quality_factor - 1);

		return sdxn;
	}

	double SetShelvingHigh(AudioProcessData data) {
		const double a = sin(data.inputs) / (quality_factor * 2);
		const double s = s * log(10) / 40 * sin(two_band_state.lpf_n0) / two_band_state.lpf_n0 * (a/* ^2 */ - 1); // Available [online]: https://www.musicdsp.org/en/latest/Filters/197-rbj-audio-eq-cookbook.html

		double theta = 2 * M_PI * corner_frequency / s;
		double mu = 10 * gain_boostcut_db / 20;
		double beta = (1 + mu) / 4;
		double bt = beta * tan(theta / 2);
		double dyn = (1 - bt) /  (1 + bt);

		double a0 = (1 + dyn) / 2;
		double a1 = -((1 + dyn) / 2); // TODO: possible inverse method?

		double b1 = -dyn;
		double b2 = 0.000;

		double c0 = mu - 10;
		
		double d0 = 1.000;
		double sdxn = 1 / (/* s^2+ */s / quality_factor + 1);

		return sdxn;
	}
private:
	BiquadFilter low_shelf;
	BiquadFilter high_shelf;

	TwoBandState two_band_state;
	TwoBandShelfParameter parameters;

	double corner_frequency;
	double quality_factor;
	double gain_boostcut_db;
};

#endif
