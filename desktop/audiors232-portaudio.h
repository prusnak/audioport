#ifndef AUDIORS232_PORTAUDIO_H
#define AUDIORS232_PORTAUDIO_H

#include <portaudio.h>
#include "audiors232-common.h"

class AudioRS232
{
public:
	AudioRS232();
	~AudioRS232();
	void send(const char *str);
	void send2(const char *str);
	CyclicBuffer *cb1, *cb2;
private:
	PaStream *stream;
};

int paCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData);

#endif
