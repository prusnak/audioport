#include "audioport-portaudio.h"

#define SAMPRATE 48000
#define FRAMES 8192
#define BITLEN 8

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
			for (unsigned long i = 0; i < framesPerBuffer / BITLEN / 16; ++i) {
				//convertSendRS232 will write 16 * BITLEN frames
				convertSendRS232(buf, audio->cb->get(), BITLEN);
				buf += 16 * BITLEN * 2;
			}
			break;
		case MODE_CUSTOM:
			for (unsigned long i = 0; i < framesPerBuffer / BITLEN / 16; ++i) {
				//convertSendCustom will write 16 * BITLEN frames
				convertSendCustom(buf, audio->cb->get(), BITLEN);
				buf += 16 * BITLEN * 2;
			}
			break;
	}

	return paContinue;
}

void AudioPort::send(const char *str)
{
	cb->put(str);
}
