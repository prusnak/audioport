#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	audio = NULL;
}

MainWindow::~MainWindow()
{
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

void MainWindow::on_editTX_returnPressed()
{
	if (ui->editTX->text().length() == 0) return;
	ui->listTX->addItem(ui->editTX->text());
	if (ui->listTX->count() > MAXITEMS) {
		ui->listTX->takeItem(0);
	}
	audio->send1 += ui->editTX->text() + getEOL();
	ui->editTX->setText("");
}

void MainWindow::on_editTX2_returnPressed()
{
	if (ui->editTX2->text().length() == 0) return;
	ui->listTX2->addItem(ui->editTX2->text());
	if (ui->listTX2->count() > MAXITEMS) {
		ui->listTX2->takeItem(0);
	}
	audio->send2 += ui->editTX2->text() + getEOL();
	ui->editTX2->setText("");
}
