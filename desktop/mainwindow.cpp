#include <QInputDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	presetButtons = new PresetButton *[20];
	for (int i = 0; i < 20; ++i) {
		presetButtons[i] = new PresetButton(this, i);
	}

	serial = new AudioRS232();
}

MainWindow::~MainWindow()
{
	delete presetButtons;
	delete serial;
	delete ui;
}

QString MainWindow::getEOL()
{
	switch (ui->comboEOL->currentIndex()) {
		case 1: return "\r";
		case 2: return "\r\n";
		case 3: return "\n";
	}
	return "";
}

#define MAXITEMS 18

void MainWindow::sendTX(QString str)
{
	ui->listComm->addItem(str.prepend("> "));
	if (ui->listComm->count() > MAXITEMS) {
		ui->listComm->takeItem(0);
	}
	serial->send( (str + getEOL()).toLatin1().constData() );
}

void MainWindow::on_editTX_returnPressed()
{
	if (ui->editTX->text().length() == 0) return;
	sendTX(ui->editTX->text());
	ui->editTX->setText("");
}
