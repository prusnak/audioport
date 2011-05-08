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
	void send(QString str);
private:
	QAudioInput* input;
	QAudioOutput* output;
private slots:
	void finishedPlaying(QAudio::State state);
};

#endif // AUDIO_H
