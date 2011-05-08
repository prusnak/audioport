#include <QtMultimedia>
#include <QTest>

QBuffer buf;
QAudioFormat format;
QAudioInput* input;
QAudioOutput* output;
QAudioDeviceInfo info;

bool init()
{
    QAudioFormat format;
    format.setFrequency(48000);
    format.setChannels(2);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    info = QAudioDeviceInfo::defaultInputDevice();
    if (!info.isFormatSupported(format)) {
        return false;
    }

    info = QAudioDeviceInfo::defaultOutputDevice();
    if (!info.isFormatSupported(format)) {
        return false;
    }

    input = new QAudioInput(format);
    output = new QAudioOutput(format);

    return true;
}

void record()
{
    input->start(&buf);
    QTest::qWait(1000);
    input->stop();
}

void playback()
{
    output->start(&buf);
    QTest::qWait(1000);
    output->stop();
}

void stop()
{
   delete input;
   delete output;
}

int main(int argc, char **argv) {
    QCoreApplication app(argc, argv);

    if (!init()) return 1;

//    for (;;) {
        record();
        playback();
//    }

    stop();

    return 0;
}
