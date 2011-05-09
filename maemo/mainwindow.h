#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "audio.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	inline void setAudio(Audio *audio) { this->audio = audio; }

private slots:
	void on_editTX_returnPressed();
	void on_editTX2_returnPressed();

private:
	Ui::MainWindow *ui;
	Audio *audio;
	QString getEOL();
};

#endif // MAINWINDOW_H
