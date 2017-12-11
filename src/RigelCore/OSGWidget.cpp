#include "OSGWidget.h"
#include <osgViewer/ViewerEventHandlers>
#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>

OSGWidget::OSGWidget(QWidget* parent)
	:QGLWidget(parent)
{
	m_pViewer = NULL;
	m_pGraphicsWindow = NULL;
	setMouseTracking(true);
	init();
}

OSGWidget::~OSGWidget()
{
}

void OSGWidget::init()
{
	m_pViewer = new osgViewer::Viewer;
	m_pViewer->setUpViewerAsEmbeddedInWindow(0, 0, width(), height());
	m_pViewer->addEventHandler(new osgViewer::StatsHandler);
	m_pViewer->addEventHandler(new osgViewer::ThreadingHandler);
	auto* osgGC = m_pViewer->getCamera()->getGraphicsContext();
	m_pGraphicsWindow = dynamic_cast<osgViewer::GraphicsWindow*>(osgGC);
	osg::DisplaySettings::instance()->setDoubleBuffer(true);
 	connect(&m_timer, SIGNAL(timeout()), this, SLOT(updateGL()));
 	m_timer.start(16);
}

osg::Camera* OSGWidget::createCamera(int x, int y, int w, int h)
{
	return nullptr;
}

void OSGWidget::setGraphicsWindow(osgViewer::GraphicsWindow* graphicsWindow)
{
	m_pGraphicsWindow = graphicsWindow;
}

void OSGWidget::paintGL()
{
	m_pViewer->frame();
}

void OSGWidget::resizeEvent(QResizeEvent *e)
{
	m_pGraphicsWindow->resized(x(), y(), width(), height());
	m_pGraphicsWindow->getEventQueue()->windowResize(x(), y(), width(), height());
	m_pGraphicsWindow->requestRedraw();
	//m_pViewer->getCamera()->setViewport(0, 0, width(), height());
}
