#include "MainWindow.h"
#include <osgDB/ReadFile>
#include "Core.h"
#include "GeoMetry/GeometryStrip.h"
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
	auto array = new osg::Vec3Array;
	array->push_back(osg::Vec3(0, 0, 0));
	array->push_back(osg::Vec3(5, 0, 0));
	array->push_back(osg::Vec3(5, 10, 0));
	array->push_back(osg::Vec3(8, 3, 0));
	GeometryStrip* floor = new GeometryStrip(array);
	//floor->setTexture(FileUtils::ins()->getPath("Data/Images/arraw_strip.png").toStdString());
	//Core::ins()->getSceneData()->addChild(osgDB::readNodeFile(
		//FileUtils::ins()->getPath("/Data/Models/cow.osg").toLocal8Bit().data()));
	Core::ins()->getSceneData()->addChild(floor);
	Core::ins()->getManipulator()->home(0);
}
