#include <limits.h>
#include "audiors232-portaudio.h"

#define SAMPRATE 48000
#define BUFSIZE 9600
#define CHARLEN 128
#define BITLEN 8

AudioRS232::AudioRS232()
{
	cb = new CyclicBuffer(16384);
	if (paNoError != Pa_Initialize())
		return;
	if (paNoError != Pa_OpenDefaultStream(&stream, 2, 2, paInt16, SAMPRATE, BUFSIZE, paCallback, this))
		return;;
	Pa_StartStream(stream);
}

AudioRS232::~AudioRS232()
{
	Pa_StopStream(stream);
	Pa_CloseStream(stream);
	Pa_Terminate();
	delete cb;
}

int paCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
{
	AudioRS232 *audio = (AudioRS232 *)userData;
	for (int i = 0; i < BUFSIZE / CHARLEN; ++i) {
		short *buf = (short *)outputBuffer;
		convertSend(buf, audio->cb->get(), SHRT_MAX, CHARLEN, BITLEN);
		buf += CHARLEN;
	}
	return paContinue;
}

void AudioRS232::send(const char *str)
{
	cb->put(str);
}
