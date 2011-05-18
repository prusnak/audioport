#include <limits.h>
#include "audiors232-portaudio.h"

#include <stdio.h>

#define SAMPRATE 48000
#define CHARLEN 128
#define BITLEN 8

AudioRS232::AudioRS232()
{
	cb = new CyclicBuffer(16384);
	if (paNoError != Pa_Initialize())
		return;
	if (paNoError != Pa_OpenDefaultStream(&stream, 2, 2, paInt16, SAMPRATE, CHARLEN, paCallback, this))
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
	printf("%d\n", framesPerBuffer);
	AudioRS232 *audio = (AudioRS232 *)userData;
	convertSend((short *)outputBuffer, audio->cb->get(), SHRT_MAX, framesPerBuffer, BITLEN);
	return paContinue;
}

void AudioRS232::send(const char *str)
{
	cb->put(str);
}
