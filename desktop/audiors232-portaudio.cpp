#include "audiors232-portaudio.h"

AudioRS232::AudioRS232()
{
	cb1 = new CyclicBuffer(16384);
	cb2 = new CyclicBuffer(16384);
	if (paNoError != Pa_Initialize())
		return;
	if (paNoError != Pa_OpenDefaultStream(&stream, 2, 2, paInt16, 48000, 128, paCallback, this))
		return;;
	Pa_StartStream(stream);
}

AudioRS232::~AudioRS232()
{
	Pa_StopStream(stream);
	Pa_CloseStream(stream);
	Pa_Terminate();
	delete cb1;
	delete cb2;
}

int paCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
{
	AudioRS232 *audio = (AudioRS232 *)userData;
	convertSend((short *)outputBuffer, audio->cb1->get(), audio->cb2->get(), 32000, framesPerBuffer, 8);
	return paContinue;
}

void AudioRS232::send(const char *str)
{
	cb1->put(str);
}

void AudioRS232::send2(const char *str)
{
	cb2->put(str);
}
