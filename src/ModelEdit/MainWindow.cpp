#include "MainWindow.h"
#include <osgDB/ReadFile>
#include "Core.h"
#include "GeoMetry/GeometryFloor.h"
#include <osgDB/ReadFile>
#include "MECore/FileUtils.h"


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	auto* osgView = new OSGGraphView;
	setCentralWidget(osgView);
	Core::ins()->init(osgView);
	initScene();
}

void MainWindow::initScene()
{
	GeometryFloor* floor = new GeometryFloor(50, 50);
	Core::ins()->getSceneData()->addChild(osgDB::readNodeFile(FileUtils::ins()->getPath("/Data/Models/cow.osg").toLocal8Bit().data()));
	Core::ins()->getSceneData()->addChild(floor);
	Core::ins()->getManipulator()->home(0);
}
