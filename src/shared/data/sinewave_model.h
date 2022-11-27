#include <cstdio> // vsnprintf, sscanf, printf
#include <cstdlib> // NULL, malloc, free, atoi
#include <cassert>

#define _USE_MATH_DEFINES
#include <cmath>

#define TABLE_SIZE 256

#ifndef SINEWAVE_MODEL
#define SINEWAVE_MODEL

typedef struct SineWave {
    double curve_value = 0.0000;
    float table_size[TABLE_SIZE];
    int phase = 0;
    int current_channel = 1;
    int cycle_count = 0;

    int left_input;
    int right_input;

    int left_phase;
    int right_phase;

    void* (dispose_sine_wave);
} SineWave;

typedef struct SineWaveVirtualTable {
    int(*OpenDevice)(SineWave *self, int device_index);
    int(*CloseDevice)(SineWave *self);
    int(*StartDevice)(SineWave *self);
    int(*StopDevice)(SineWave *self);
} SineWaveVirtualTable;

typedef void(ImposeSineWave)(SineWave* sine_wave);
typedef void(DisposeSineWave)(SineWave*);

static int(*StreamDevice)(SineWaveVirtualTable* sine_wave, int channel);
static int(*DeviceLeftPhase)(SineWaveVirtualTable* sine_wave, int channel);
static int(*DeviceRightPhase)(SineWaveVirtualTable*sine_wave, int channel);

SineWave CreateSineWave(SineWave sine_wave) {
	return sine_wave;
}

void DestroySineWave(SineWave* sine_wave) {
    realloc(sine_wave, sizeof(SineWave));
	free(&sine_wave);
}

void TeardownSinusoid(SineWave* sine_wave) {
	assert(sine_wave);
	sine_wave->dispose_sine_wave = DestroySineWave;
}

#endif