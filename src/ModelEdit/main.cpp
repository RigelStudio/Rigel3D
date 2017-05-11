#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include "Core.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Core::ins()->init();

	MainWindow w;
	w.show();
	return a.exec();
}
