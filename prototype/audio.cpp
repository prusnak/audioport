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

#define TOTALLEN (128)
#define BITLEN (8)
#define WAITLEN ((TOTALLEN)-10*(BITLEN))
#define VALUE (0.75f)

bool Audio::setup() {
	err = Pa_Initialize();
	if (err != paNoError) return false;
	err = Pa_OpenDefaultStream(&stream, 2, 2, paFloat32, 48000, TOTALLEN, paCallback, this);
	if (err != paNoError) return false;
	err = Pa_StartStream(stream);
	if (err != paNoError) return false;
	return true;
}

int paCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData) {
	Audio *audio = (Audio *)userData;
	float *out = (float *)outputBuffer;
	const float *in = (const float *)inputBuffer;

	bool sending1 = audio->send1.length() > 0;
	bool sending2 = audio->send2.length() > 0;
	char c1 = audio->send1.toLatin1().constData()[0];
	char c2 = audio->send2.toLatin1().constData()[0];

	// start bit
	for (int i = 0; i < BITLEN; ++i) {
		// left
		if (sending1) {
			*out++ = +VALUE;
		} else {
			*out++ = 0;
		}
		// right
		if (sending2) {
			*out++ = +VALUE;
		} else {
			*out++ = 0;
		}
	}

	// send char
	for (int b = 0; b < 8; ++b) {
		for (int i = 0; i < BITLEN; ++i) {
			// left
			if (sending1) {
				*out++ = (c1 & (1 << b)) ? -VALUE : +VALUE;
			} else {
				*out++ = 0;
			}
			// right
			if (sending2) {
				*out++ = (c2 & (1 << b)) ? -VALUE : +VALUE;
			} else {
				*out++ = 0;
			}
		}
	}

	// stop bit
	for (int i = 0; i < BITLEN; ++i) {
		// left
		if (sending1) {
			*out++ = -VALUE;
		} else {
			*out++ = 0;
		}
		// right
		if (sending2) {
			*out++ = -VALUE;
		} else {
			*out++ = 0;
		}
	}

	// wait
	for (int i = 0; i < WAITLEN; ++i) {
		// left
		*out++ = 0;
		// right
		*out++ = 0;
	}

	if (sending1) audio->send1.remove(0, 1);
	if (sending2) audio->send2.remove(0, 1);

	return paContinue;
}
