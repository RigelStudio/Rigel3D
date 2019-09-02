#include <QGuiApplication>
#include "qqmlapplicationengine.h"
#include "RigelQt/OSGView.h"
#include "RigelCore/FileUtils.h"

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);
	auto strDir = QGuiApplication::applicationDirPath().toStdString();
	//FileUtils::ins()->init(strDir);
	qmlRegisterType<OSGView>("OSGQuick.OSGView", 1, 0, "OSGView");
	QQmlApplicationEngine engine;
	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
	return app.exec();
}
