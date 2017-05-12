#include "MainWindow.h"
#include <osgDB/ReadFile>
#include <QMenuBar>
#include "Core.h"
#include "GeoMetry/GeometryStrip.h"
#include <osgDB/ReadFile>
#include "MECore/FileUtils.h"
#include "MECore/GraphicsView.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	GraphicsView* pView = new GraphicsView(this);
	setCentralWidget(pView);
	Core::ins()->init(pView);
	initScene();
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
	m_pTitleWidget->setGeometry(QRect(0, 0, this->geometry().width(), 90));
}

void MainWindow::initScene()
{
	initSimon();
	//initKestiny();
	Core::ins()->getManipulator()->home(0);
}

void MainWindow::initSimon()
{
	auto array = new osg::Vec3Array;
	array->push_back(osg::Vec3(0, 0, 0));
	array->push_back(osg::Vec3(5, 0, 0));
	array->push_back(osg::Vec3(5, 10, 0));
	array->push_back(osg::Vec3(8, 3, 0));
	GeometryStrip* floor = new GeometryStrip(array);
	floor->setTexture(FileUtils::ins()->getPath("Data/Images/arraw_strip.png").toStdString());
	Core::ins()->getSceneData()->addChild(floor);
}

void MainWindow::initKestiny()
{
	// 初始化标题栏
	m_pAppTitle = new AppHeadeTitle;
	m_pTitleWidget = Core::ins()->getGraphScene()->addWidget(m_pAppTitle);
	m_pTitleWidget->show();
	m_pTitleWidget->setGeometry(QRect(0, 0, this->width(), 90));

	Core::ins()->getSceneData()->addChild(osgDB::readNodeFile(
		FileUtils::ins()->getPath("Data/Models/cow.osg").toLocal8Bit().data()));
}
