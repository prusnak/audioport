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

QString MainWindow::getEOL() {
	switch (ui->comboEOL->currentIndex()) {
		case 1: return "\r";
		case 2: return "\r\n";
		case 3: return "\n";
	}
	return "";
}

void MainWindow::on_editTX_returnPressed()
{
	if (ui->editTX->text().length() == 0) return;
	ui->listTX->addItem(ui->editTX->text());
	audio->send(ui->editTX->text() + getEOL());
	ui->editTX->setText("");
}

void MainWindow::on_editTX2_returnPressed()
{
	if (ui->editTX2->text().length() == 0) return;
	ui->listTX2->addItem(ui->editTX2->text());
	audio->send(ui->editTX2->text() + getEOL());
	ui->editTX2->setText("");
}
