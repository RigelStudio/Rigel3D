#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "RigelQt/OSGView.h"
#include "RigelCore/FileUtils.h"

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);
	auto strDir = QGuiApplication::applicationDirPath().toStdString();
	FileUtils::ins()->init(strDir);
	QQmlApplicationEngine engine;
	engine.load(QUrl(QStringLiteral("qrc:/TopPanel.qml")));
	return app.exec();
}
