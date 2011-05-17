#include <QtGui/QApplication>
#include <QtGui/QMessageBox>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QCoreApplication::setOrganizationName("brmlab");
	QCoreApplication::setOrganizationDomain("brmlab.cz");
	QCoreApplication::setApplicationName("AudioRS232");

	MainWindow window;
#ifdef MAEMO
	window.showFullScreen();
#else
	window.show();
#endif

	return app.exec();
}
