#include <QInputDialog>
#include "presetbutton.h"
#include "mainwindow.h"

PresetButton::PresetButton(QWidget *parent, int index) : QPushButton(parent)
{
	this->setText( settings.value(QString("preset%1").arg(index + 1), "").toString() );
	this->setGeometry(420 + index / 7 * 190, 10 + 58 * (index % 7), 181, 51);
	this->index = index;
}

PresetButton::~PresetButton()
{
}

bool PresetButton::eventFilter(QObject *obj, QEvent *e)
{
	if (e->type() == QEvent::ContextMenu) {
		this->setPreset();
		return false;
	} else {
		return QPushButton::eventFilter(obj, e);
	}
}

void PresetButton::mouseReleaseEvent(QMouseEvent *e)
{
	QPushButton::mouseReleaseEvent(e);
	if (e->button() == Qt::LeftButton) {
		((MainWindow *)this->parentWidget())->sendTX(this->text());
	}
	if (e->button() == Qt::RightButton) {
		this->setPreset();
	}
}

void PresetButton::setPreset() {
	bool ok;
	QString str = QInputDialog::getText(this, QString("Preset #%1").arg(index + 1), QString("Enter preset #%1:").arg(index + 1), QLineEdit::Normal, this->text(), &ok);
	if (!ok) return;
	this->setText(str);
	settings.setValue(QString("preset%1").arg(index + 1), str);
}
