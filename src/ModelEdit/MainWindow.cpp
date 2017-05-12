#include "MainWindow.h"
#include <osgDB/ReadFile>
#include <QMenuBar>
#include "Core.h"
#include "GeoMetry/GeometryFloor.h"
#include <osgDB/ReadFile>
#include "MECore/FileUtils.h"
#include "MECore/GraphicsView.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	initScene();
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
	m_pTitleWidget->setGeometry(QRect(0, 0, this->geometry().width(), 90));
}

void MainWindow::initScene()
{
	GraphicsView* pView = new GraphicsView(this);
	setCentralWidget(pView);
	Core::ins()->init(pView);

	// 初始化标题栏
	m_pAppTitle = new AppHeadeTitle;
	m_pTitleWidget = Core::ins()->getGraphScene()->addWidget(m_pAppTitle);
	m_pTitleWidget->show();
	m_pTitleWidget->setGeometry(QRect(0, 0, this->width(), 90));

	GeometryFloor* floor = new GeometryFloor(50, 50);
	Core::ins()->getSceneData()->addChild(osgDB::readNodeFile(FileUtils::ins()->getPath("/Data/Models/cow.osg").toLocal8Bit().data()));
	Core::ins()->getSceneData()->addChild(floor);
	Core::ins()->getManipulator()->home(0);
}
