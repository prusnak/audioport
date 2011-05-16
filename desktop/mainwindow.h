#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "audiors232-portaudio.h"
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
	void sendTX2(QString str);

private slots:
	void on_editTX_returnPressed();
	void on_editTX2_returnPressed();
	void on_pushPresets_clicked(bool checked);

private:
	Ui::MainWindow *ui;
	PresetButton **presetButtons;
	AudioRS232 *serial;
	QString getEOL();
};

#endif
