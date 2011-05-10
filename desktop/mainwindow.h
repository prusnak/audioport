#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "audiors232.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_editTX_returnPressed();
	void on_editTX2_returnPressed();

private:
	Ui::MainWindow *ui;
	AudioRS232 *serial;
	QString getEOL();
};

#endif
