#ifndef PRESETBUTTON_H
#define PRESETBUTTON_H

#include <QPushButton>
#include <QSettings>
#include <QMouseEvent>

class PresetButton : public QPushButton {
	Q_OBJECT
public:
	explicit PresetButton(QWidget *parent = 0, int index = 0);
	~PresetButton();
protected:
	bool eventFilter(QObject *obj, QEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
	void setPreset();
	QSettings settings;
	int index;
};

#endif
