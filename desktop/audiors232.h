#ifndef AUDIORS232_H
#define AUDIORS232_H

#include <portaudio.h>

int paCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData);

#define BUFSIZE 10

class AudioRS232
{
public:
	AudioRS232();
	~AudioRS232();
	void send(const char *str);
	void send2(const char *str);

//private:
	PaStream *stream;
	char buf1[BUFSIZE];
	char buf2[BUFSIZE];
	int start1, start2;
	int end1, end2;
};

#endif
