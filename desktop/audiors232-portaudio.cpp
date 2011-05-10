#include "audiors232-portaudio.h"
#include "audiors232-common.h"

#define BITLEN 8

AudioRS232::AudioRS232() : start1(0), start2(0), end1(0), end2(0)
{
	bufsize = 16384;
	buf1 = new char[bufsize];
	buf2 = new char[bufsize];
	Pa_Initialize();
	Pa_OpenDefaultStream(&stream, 2, 2, paInt16, 48000, 128, paCallback, this);
	Pa_StartStream(stream);
}

AudioRS232::~AudioRS232()
{
	Pa_StopStream(stream);
	Pa_CloseStream(stream);
	Pa_Terminate();
	delete buf1;
	delete buf2;
}

int paCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
{
	AudioRS232 *audio = (AudioRS232 *)userData;

	short c1 = (audio->start1 != audio->end1) ? audio->buf1[audio->start1] : -1;
	short c2 = (audio->start2 != audio->end2) ? audio->buf2[audio->start2] : -1;

	convertSend((short *)outputBuffer, c1, c2, 32000, framesPerBuffer, BITLEN);

	if (c1 >= 0) audio->start1 = (audio->start1 + 1) % (audio->bufsize);
	if (c2 >= 0) audio->start2 = (audio->start2 + 1) % (audio->bufsize);

	return paContinue;
}

void AudioRS232::send(const char *str)
{
	for (const char *c = str; *c; ++c) {
		if (end1 + 1 == start1) break;
		buf1[end1] = *c;
		end1 = (end1 + 1) % bufsize;
	}
}

void AudioRS232::send2(const char *str)
{
	for (const char *c = str; *c; ++c) {
		if (end2 + 1 == start2) break;
		buf2[end2] = *c;
		end2 = (end2 + 1) % bufsize;
	}
}
