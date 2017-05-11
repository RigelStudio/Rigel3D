#include "MainWindow.h"
#include <QApplication>
#include "Core.h"
#include "MECore/FileUtils.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	FileUtils::ins()->init(QApplication::applicationDirPath().append("/../"));
	Core::ins()->init();

	MainWindow w;
	w.show();
	return a.exec();
}
