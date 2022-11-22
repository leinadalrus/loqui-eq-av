#ifndef WAVESHAPER_H
#define WAVESHAPER_H

enum class Waveshapes {
	SGN,
	ATAN,
	TANH,
	SOFT_CLIP,
	FUZZ_EXP,
};

class Waveshaper {
public:
	void* sgn();
	void* atan();
	void* tanh();
	void* soft_clip();
	void* fuzz_exp();
};

#endif

