#ifndef AUDIOPORT_PORTAUDIO_H
#define AUDIOPORT_PORTAUDIO_H

#include <portaudio.h>
#include "audioport-common.h"

class AudioPort
{
public:
	AudioPort();
	~AudioPort();
	bool start();
	void send(const char *str);
	CyclicBuffer *cb;
private:
	PaStream *stream;
};

int paCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData);

#endif
