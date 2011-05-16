#include <QInputDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	presetButtons = new PresetButton *[40];
	for (int i = 0; i < 40; ++i) {
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

#define MAXITEMS 16

void MainWindow::sendTX(QString str)
{
	ui->listTX->addItem(str);
	if (ui->listTX->count() > MAXITEMS) {
		ui->listTX->takeItem(0);
	}
	serial->send( (str + getEOL()).toLatin1().constData() );
}

void MainWindow::sendTX2(QString str)
{
	ui->listTX2->addItem(str);
	if (ui->listTX2->count() > MAXITEMS) {
		ui->listTX2->takeItem(0);
	}
	serial->send2( (str + getEOL()).toLatin1().constData() );
}

void MainWindow::on_editTX_returnPressed()
{
	if (ui->editTX->text().length() == 0) return;
	sendTX(ui->editTX->text());
	ui->editTX->setText("");
}

void MainWindow::on_editTX2_returnPressed()
{
	if (ui->editTX2->text().length() == 0) return;
	sendTX2(ui->editTX2->text());
	ui->editTX2->setText("");
}

void MainWindow::on_pushPresets_clicked(bool checked)
{
	ui->listTX->setVisible(!checked);
	ui->listTX2->setVisible(!checked);
	for (int i = 0; i < 40; ++i) {
		presetButtons[i]->setVisible(checked);
	}
}

/*
void MainWindow::presetButton_clicked(int which)
{
	QString str = presetButtons[which]->text();
	if (which < 20) {
		sendTX(str);
		serial->send( (str + getEOL()).toLatin1().constData() );
	} else {
		sendTX2(str);
		serial->send2( (str + getEOL()).toLatin1().constData() );
	}
}
*/
