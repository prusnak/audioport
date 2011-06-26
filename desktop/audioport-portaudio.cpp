#include "audioport-portaudio.h"

#include <stdio.h>

#define SAMPRATE 44100
#define FRAMES 8192

AudioPort::AudioPort(AudioPortMode _mode) : mode(_mode)
{
	cb = new CyclicBuffer(16384);
}

AudioPort::~AudioPort()
{
	Pa_StopStream(stream);
	Pa_CloseStream(stream);
	Pa_Terminate();
	delete cb;
}

bool AudioPort::start()
{
	if (paNoError != Pa_Initialize())
		return false;
	if (paNoError != Pa_OpenDefaultStream(&stream, 2, 2, paInt16, SAMPRATE, FRAMES, paCallback, this))
		return false;
	if (paNoError != Pa_StartStream(stream))
		return false;
	return true;
}

int paCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
{
	AudioPort *audio = (AudioPort *)userData;
	short *buf = (short *)outputBuffer;

	switch (audio->mode) {
		case MODE_RS232:
			// convertSendRS232 will write 32 frames
			for (unsigned long i = 0; i < framesPerBuffer/32; ++i) {
				convertSendRS232(buf, audio->cb->get());
				buf += 2 * 32;
			}
			break;
		case MODE_MANCHESTER:
			//convertSendCustom will write 64 frames
			for (unsigned long i = 0; i < framesPerBuffer/64; ++i) {
				convertSendManchester(buf, audio->cb->get());
				buf += 2 * 64;
			}
			break;
		case MODE_RZ:
			//convertSendCustom will write 64 frames
			for (unsigned long i = 0; i < framesPerBuffer/64; ++i) {
				convertSendRZ(buf, audio->cb->get());
				buf += 2 * 64;
			}
			break;
	}

	return paContinue;
}

void AudioPort::send(const char *str)
{
	cb->put(str);
}
