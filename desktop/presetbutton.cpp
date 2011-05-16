#include <QInputDialog>
#include "presetbutton.h"
#include "mainwindow.h"

PresetButton::PresetButton(QWidget *parent, int index) : QPushButton(parent)
{
	this->setText( settings.value(QString("preset%1").arg(index), "").toString() );
	this->setGeometry(280 + index / 10 * 130, 40 + 40 * (index % 10), 121, 31);
	this->setVisible(false);
	this->index = index;
}

PresetButton::~PresetButton()
{
}

void PresetButton::mouseReleaseEvent(QMouseEvent *e)
{
	QPushButton::mouseReleaseEvent(e);
	if (e->button() == Qt::LeftButton) {
		if (index < 20) {
			((MainWindow *)this->parentWidget())->sendTX(this->text());
		} else {
			((MainWindow *)this->parentWidget())->sendTX2(this->text());
		}
	}
	if (e->button() == Qt::RightButton) {
		bool ok;
		QString str = QInputDialog::getText(this, QString("Preset #%1").arg(index), QString("Enter preset #%1:").arg(index), QLineEdit::Normal, this->text(), &ok);
		if (!ok) return;
		this->setText(str);
		settings.setValue(QString("preset%1").arg(index), str);
	}
}
