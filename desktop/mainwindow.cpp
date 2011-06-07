#include <QInputDialog>
#include <QMessageBox>
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	presetButtons = new PresetButton *[14];
	for (int i = 0; i < 14; ++i) {
		presetButtons[i] = new PresetButton(this, i);
	}

	serial = new AudioPort();
	qDebug() << serial->start();
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

QString MainWindow::escape(QString str)
{
	QString::ConstIterator it = str.begin();
	QString::ConstIterator ite = str.end();
	QString newstr;
	for (; it != ite; ++it) {
		if (it->toLatin1() < ' ') {
			QString hex("%1");
			newstr += hex.arg(it->toLatin1(), 2, 16, QChar('0')).toUpper().prepend("\\x");
		} else {
			newstr += *it;
		}
	}
	return newstr;
}

void MainWindow::sendTX(QString str)
{
	ui->listComm->addItem(str.prepend("> "));
	ui->listComm->setCurrentRow(ui->listComm->count() - 1);
	str += getEOL();
	serial->send( str.toLatin1().constData() );
}

void MainWindow::on_editTX_returnPressed()
{
	if (ui->editTX->text().length() == 0) return;
	sendTX(ui->editTX->text());
	ui->editTX->setText("");
}

void MainWindow::on_pushAbout_clicked()
{
	QMessageBox aboutBox(QMessageBox::NoIcon, "About AudioPort", QString::fromUtf8("AudioPort\n\nhackerspace brmlab - http://brmlab.cz/\n\nSee README for more info and COPYING for the license." ), QMessageBox::Ok, this);
	aboutBox.setIconPixmap(QPixmap(":/icons/icon.png"));
	aboutBox.exec();
}

void MainWindow::on_pushExit_clicked()
{
	this->close();
}
