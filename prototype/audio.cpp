#include "audio.h"

Audio::Audio() : QObject()
{
}

Audio::~Audio() {
	delete input;
	delete output;
}

bool Audio::setup() {
	QAudioDeviceInfo info;
	QAudioFormat format;
	format.setSampleRate(48000);
	format.setChannelCount(2);
	format.setSampleSize(16);
	format.setCodec("audio/pcm");
	format.setByteOrder(QAudioFormat::LittleEndian);
	format.setSampleType(QAudioFormat::SignedInt);

	info = QAudioDeviceInfo::defaultOutputDevice();
	if (!info.isFormatSupported(format)) {
		return false;
	}

	info = QAudioDeviceInfo::defaultInputDevice();
	if (!info.isFormatSupported(format)) {
		return false;
	}

	input = new QAudioInput(format);
	output = new QAudioOutput(format);

	connect(output, SIGNAL(stateChanged(QAudio::State)), SLOT(finishedPlaying(QAudio::State)));

	return true;
}

void Audio::send(QString str) {
	QBuffer buf;
	for (int i = 0; i < 1000; ++i) {
		buf.write("\x40\x40\x40\x40\x40\x40\x40\x40\xC0\xC0\xC0\xC0\xC0\xC0\xC0\xC0");
	}
	output->start(&buf);
}

void Audio::finishedPlaying(QAudio::State state)
{
	if(state == QAudio::IdleState) {
		output->stop();
	}
}
