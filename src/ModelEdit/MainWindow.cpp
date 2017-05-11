#include "MainWindow.h"
#include "Core.h"
#include "GeoMetryModel/GeometryFloor.h"
#include <osgDB/ReadFile>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//auto* osgView = new OSGGraphView;
	//setCentralWidget(osgView);
	setCentralWidget(Core::ins()->getOSGView());
	initScene();
}

void MainWindow::initScene()
{
	GeometryFloor* floor = new GeometryFloor(50, 50);
	Core::ins()->getSceneData()->addChild(osgDB::readNodeFile("/Data/Models/cow.osg"));
	Core::ins()->getSceneData()->addChild(floor);
	Core::ins()->getManipulator()->home(0);
}
