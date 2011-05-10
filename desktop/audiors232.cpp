#include "audiors232.h"

#define TOTALLEN (128)
#define BITLEN (8)
#define WAITLEN ((TOTALLEN)-10*(BITLEN))
#define VALUE (0.75f)

AudioRS232::AudioRS232() : start1(0), start2(0), end1(0), end2(0)
{
	Pa_Initialize();
	Pa_OpenDefaultStream(&stream, 2, 2, paFloat32, 48000, TOTALLEN, paCallback, this);
	Pa_StartStream(stream);
}

AudioRS232::~AudioRS232()
{
	Pa_StopStream(stream);
	Pa_CloseStream(stream);
	Pa_Terminate();
}

int paCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
{
	AudioRS232 *audio = (AudioRS232 *)userData;
	float *out = (float *)outputBuffer;
	const float *in = (const float *)inputBuffer;

	// start bit
	for (int i = 0; i < BITLEN; ++i) {
		// left
		if (audio->start1 != audio->end1) {
			*out++ = +VALUE;
		} else {
			*out++ = 0;
		}
		// right
		if (audio->start2 != audio->end2) {
			*out++ = +VALUE;
		} else {
			*out++ = 0;
		}
	}

	// send char
	for (int b = 0; b < 8; ++b) {
		for (int i = 0; i < BITLEN; ++i) {
			// left
			if (audio->start1 != audio->end1) {
				*out++ = (audio->buf1[audio->start1] & (1 << b)) ? -VALUE : +VALUE;
			} else {
				*out++ = 0;
			}
			// right
			if (audio->start2 != audio->end2) {
				*out++ = (audio->buf2[audio->start2] & (1 << b)) ? -VALUE : +VALUE;
			} else {
				*out++ = 0;
			}
		}
	}

	// stop bit
	for (int i = 0; i < BITLEN; ++i) {
		// left
		if (audio->start1 != audio->end1) {
			*out++ = -VALUE;
		} else {
			*out++ = 0;
		}
		// right
		if (audio->start2 != audio->end2) {
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

	if (audio->start1 != audio->end1) audio->start1 = (audio->start1 + 1) % BUFSIZE;
	if (audio->start2 != audio->end2) audio->start2 = (audio->start2 + 1) % BUFSIZE;

	return paContinue;
}

void AudioRS232::send(const char *str)
{
	for (const char *c = str; *c; ++c) {
		if (end1 + 1 == start1) break;
		buf1[end1] = *c;
		end1 = (end1 + 1) % BUFSIZE;
	}
}

void AudioRS232::send2(const char *str)
{
	for (const char *c = str; *c; ++c) {
		if (end2 + 1 == start2) break;
		buf2[end2] = *c;
		end2 = (end2 + 1) % BUFSIZE;
	}
}
