#ifndef AUDIO_H
#define AUDIO_H

#include <portaudio.h>

int paCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData);

class Audio
{
public:
	Audio();
	~Audio();
	bool setup();
	QString tosend1;
	QString tosend2;
private:
	PaStream *stream;
	PaError err;
};

#endif // AUDIO_H
