#include "audio.h"
#include <math.h>

Audio::Audio()
{
}

Audio::~Audio() {
	Pa_StopStream(stream);
	Pa_CloseStream(stream);
	Pa_Terminate();
}

bool Audio::setup() {
	err = Pa_Initialize();
	if (err != paNoError) return false;
	err = Pa_OpenDefaultStream(&stream, 2, 2, paFloat32, 48000, 256, paCallback, this);
	if (err != paNoError) return false;
	err = Pa_StartStream(stream);
	if (err != paNoError) return false;
	return true;
}

int paCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData) {
	Audio *audio = (Audio *)userData;
	float *out = (float *)outputBuffer;
	const float *in = (const float *)inputBuffer;

	for(unsigned long i = 0; i < framesPerBuffer; ++i) {
		// left
		*out++ = sin(6.28*i/framesPerBuffer);
		// right
		*out++ = sin(6.28*i/framesPerBuffer);
	}

	return paContinue;
}
