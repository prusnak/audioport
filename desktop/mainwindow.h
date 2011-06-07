#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "audioport-portaudio.h"
#include "presetbutton.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	void sendTX(QString str);

private slots:
	void on_editTX_returnPressed();
	void on_pushAbout_clicked();
	void on_pushExit_clicked();

private:
	Ui::MainWindow *ui;
	PresetButton **presetButtons;
	AudioPort *serial;
	QString getEOL();
	QString escape(QString str);
};

#endif
