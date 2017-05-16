#include "graphicsview.h"
#include <QGraphicsScene>
#include <QPaintEngine>
#include <QGLWidget>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>

GraphicsView::GraphicsView(QWidget *parent)
{
	this->setScene(new QGraphicsScene);
	init();
}

GraphicsView::~GraphicsView()
{
}

void GraphicsView::init()
{
	QGLWidget* glViewPort = new QGLWidget;
	glViewPort->setMouseTracking(true);
	glViewPort->setMaximumSize(2000, 2000);
	this->setViewport(glViewPort);
	this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
	startTimer(10);

	m_pSceneData = new osg::Group;
	m_pSceneData->setName("root");

	m_pViewer = new osgViewer::Viewer;
	m_pViewer->addEventHandler(new osgViewer::StatsHandler);
	m_pViewer->getCamera()->setNearFarRatio(0.001);
	m_pViewer->getCamera()->setComputeNearFarMode(osg::CullSettings::COMPUTE_NEAR_FAR_USING_BOUNDING_VOLUMES);
	m_pViewer->setUpViewerAsEmbeddedInWindow(0, 0, width(), height());
	auto* manipulator = new osgGA::TrackballManipulator;
	m_pViewer->setCameraManipulator(manipulator);

	m_pViewer->setSceneData(m_pSceneData);
	m_pGraphicsWindow = dynamic_cast<osgViewer::GraphicsWindow*>(
		m_pViewer->getCamera()->getGraphicsContext());
}

void GraphicsView::timerEvent(QTimerEvent *event)
{
	this->scene()->update();
}

void GraphicsView::drawBackground(QPainter *painter, const QRectF& rect)
{
	if (painter->paintEngine()->type() != QPaintEngine::OpenGL2)
	{
		return;
	}

	// Save the painter state
	painter->save();
	painter->beginNativePainting();

	m_pViewer->frame();

	painter->endNativePainting();
	painter->restore();
}
