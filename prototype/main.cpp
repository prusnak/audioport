#include <QtGui/QApplication>
#include "mainwindow.h"
#include "audio.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	Audio *audio = new Audio();
	if (!audio->setup()) {
		QMessageBox::critical(NULL, "Audio failed", "Could not initialize audio");
		return 1;
	}

	MainWindow window;
	window.setAudio(audio);
	window.show();

	return app.exec();
}
