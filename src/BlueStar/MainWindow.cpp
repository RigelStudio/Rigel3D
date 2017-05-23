#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "MECore/OECore.h"
#include "MECore/FileUtils.h"
#include "MECore/GraphicsView.h"

#include <osg/DisplaySettings>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/StateSetManipulator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	GraphicsView* pView = new GraphicsView(this);
	setCentralWidget(pView);
	OECore::ins()->init(pView);
	osg::DisplaySettings::instance()->setNumMultiSamples(16);
}

MainWindow::~MainWindow()
{
    delete ui;
}
