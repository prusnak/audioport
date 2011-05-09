#ifndef AUDIO_H
#define AUDIO_H

#include <QtMultimedia>

class Audio : public QObject
{
	Q_OBJECT

public:
	Audio();
	~Audio();
	bool setup();
	void send(QString str, int channel);
private:
	QAudioInput* input;
	QAudioOutput* output;
	QBuffer buf;
	void genchar(const char *cstr, int len, int channel);
private slots:
	void finishedPlaying(QAudio::State state);
};

#endif // AUDIO_H
