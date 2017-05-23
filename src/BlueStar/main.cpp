#include "MainWindow.h"
#include <iostream>
#include <QApplication>
#include <QTime>
#include "MECore/FileUtils.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	FileUtils::ins()->init(QApplication::applicationDirPath().append("/../"));

	MainWindow w;
	w.showMaximized();
	return a.exec();
}
