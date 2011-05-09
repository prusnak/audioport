#include "audio.h"

Audio::Audio() : QObject()
{
}

Audio::~Audio() {
	input->stop();
	output->stop();
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

void Audio::send(QString str, int channel) {
	buf.open(QIODevice::ReadWrite);
	genchar(str.toLatin1().constData(), str.length(), channel);
	buf.seek(0);
	output->start(&buf);
}

#define BIT0L "\x40\x00\x00\x00\x40\x00\x00\x00\x40\x00\x00\x00\x40\x00\x00\x00\x40\x00\x00\x00\x40\x00\x00\x00\x40\x00\x00\x00\x40\x00\x00\x00"
#define BIT0R "\x00\x00\x40\x00\x00\x00\x40\x00\x00\x00\x40\x00\x00\x00\x40\x00\x00\x00\x40\x00\x00\x00\x40\x00\x00\x00\x40\x00\x00\x00\x40\x00"
#define BIT1L "\xC0\x00\x00\x00\xC0\x00\x00\x00\xC0\x00\x00\x00\xC0\x00\x00\x00\xC0\x00\x00\x00\xC0\x00\x00\x00\xC0\x00\x00\x00\xC0\x00\x00\x00"
#define BIT1R "\x00\x00\xC0\x00\x00\x00\xC0\x00\x00\x00\xC0\x00\x00\x00\xC0\x00\x00\x00\xC0\x00\x00\x00\xC0\x00\x00\x00\xC0\x00\x00\x00\xC0\x00"
#define BITW "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"

void Audio::genchar(const char *cstr, int len, int channel) {
	const char *BIT0 = BIT0L;
	const char *BIT1 = BIT1L;
	if (channel == 2) {
		BIT0 = BIT0R;
		BIT1 = BIT1R;
	}
	for (int i = 0; i < len; ++i) {
		const char c = cstr[i];
		buf.write(BIT0);  // STARTBIT
		buf.write(c & 0x01 ? BIT1 : BIT0);
		buf.write(c & 0x02 ? BIT1 : BIT0);
		buf.write(c & 0x04 ? BIT1 : BIT0);
		buf.write(c & 0x08 ? BIT1 : BIT0);
		buf.write(c & 0x10 ? BIT1 : BIT0);
		buf.write(c & 0x20 ? BIT1 : BIT0);
		buf.write(c & 0x40 ? BIT1 : BIT0);
		buf.write(c & 0x80 ? BIT1 : BIT0);
		buf.write(BIT1); // STOPBIT
		buf.write(BITW); // WAIT
	}
}

void Audio::finishedPlaying(QAudio::State state)
{
	if(state == QAudio::IdleState) {
		output->stop();
		buf.close();
	}
}
