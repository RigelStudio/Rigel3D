#include "OSGView.h"
#include <QQuickWindow>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>
#include <QQmlApplicationEngine>

class DLL_EXPORT OSGRender : public QQuickFramebufferObject::Renderer
{
public:
	OSGRender::OSGRender(const OSGView* view)
		: m_pViewer(view->m_pViewer)
	{
		m_pOSGView = view;
	}
	~OSGRender() {};

	QOpenGLFramebufferObject *OSGRender::createFramebufferObject(const QSize &size)
	{
		QOpenGLFramebufferObjectFormat format;
		format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
		format.setSamples(4);
		return new QOpenGLFramebufferObject(size, format);
	}

	void OSGRender::render()
	{
		QOpenGLContext::currentContext()->functions()->glUseProgram(0);
		osgGA::EventQueue::Events events;
		if (events.size() > 0)
		{
			m_pOSGView->m_pEventQueue->takeEvents(events);
			m_pOSGView->m_pViewer->getEventQueue()->appendEvents(events);
		}
		m_pOSGView->m_pViewer->frame();
		update();
	}

private:
	const OSGView* m_pOSGView;
	osg::observer_ptr<osgViewer::Viewer> m_pViewer;
};


OSGView::OSGView(QQuickItem *parent/* = Q_NULLPTR*/)
	:QQuickFramebufferObject(parent)
{
	m_pRoot = nullptr;
	m_pCamera = nullptr;
	m_pViewer = nullptr;
	setFlag(ItemHasContents, true);
	setAcceptedMouseButtons(Qt::AllButtons);
	initOSG();
	//qmlRegisterType<OSGView>("OSGQuick.OSGView", 1, 0, "OSGView");
}


OSGView::~OSGView()
{
	delete m_pViewer;
}

osg::Camera* OSGView::getCamera()
{
	return m_pCamera;
}

osgViewer::Viewer* OSGView::getViewer()
{
	return m_pViewer;
}

osg::Group* OSGView::getSceneData()
{
	return m_pRoot;
}

void OSGView::slotHome()
{
	
}

QQuickFramebufferObject::Renderer* OSGView::createRenderer() const
{
	return new OSGRender(this);
}

void OSGView::initOSG()
{
	m_pEventQueue = new osgGA::EventQueue;

	m_pViewer = new osgViewer::Viewer;
	m_pRoot = new osg::Group;
	m_pViewer->setSceneData(m_pRoot);
	m_pCamera = m_pViewer->getCamera();
	
	m_pViewer->setCameraManipulator(new osgGA::TrackballManipulator);
	auto handler = new osgViewer::StatsHandler();
	m_pViewer->addEventHandler(handler);
	m_pViewer->setThreadingModel(osgViewer::ViewerBase::SingleThreaded);

	auto context = m_pViewer->setUpViewerAsEmbeddedInWindow(0, 0, 0, 0);
	m_pCamera->setGraphicsContext(context);
	startTimer(10);
}

QSGNode * OSGView::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *nodeData)
{
	QSGNode* node = QQuickFramebufferObject::updatePaintNode(oldNode, nodeData);
	if (nullptr != node)
	{
		QSGSimpleTextureNode& textureNode = dynamic_cast<QSGSimpleTextureNode&>(*node);
		textureNode.setTextureCoordinatesTransform(QSGSimpleTextureNode::MirrorVertically);
		return node;
	}
	return node;
}

void OSGView::geometryChanged(const QRectF& newGeometry, const QRectF& oldGeometry)
{
	m_pEventQueue->windowResize(newGeometry.x(), newGeometry.y(), newGeometry.width(), newGeometry.height());
	m_pViewer->getCamera()->setViewport(new osg::Viewport(0, 0, newGeometry.width(), newGeometry.height()));
	const double aspectRatio = newGeometry.width() / newGeometry.height();
	m_pViewer->getCamera()->setProjectionMatrixAsPerspective(30.0f, aspectRatio, 1.0f, 10000.0f);
	QQuickFramebufferObject::geometryChanged(newGeometry, oldGeometry);
}

void OSGView::mousePressEvent(QMouseEvent *event)
{
	m_pEventQueue->mouseButtonPress(event->x(), event->y(), event->button());
}

void OSGView::mouseMoveEvent(QMouseEvent *event)
{
	m_pEventQueue->mouseMotion(event->x(), event->y());
	update();
}

void OSGView::mouseReleaseEvent(QMouseEvent *event)
{
	m_pEventQueue->mouseButtonRelease(event->x(), event->y(), event->button());
	update();
}

void OSGView::mouseDoubleClickEvent(QMouseEvent *event)
{
	m_pEventQueue->mouseDoubleButtonPress(event->x(), event->y(), event->button());
	update();
}

void OSGView::wheelEvent(QWheelEvent *event)
{
	if (event->delta() > 0)
		m_pEventQueue->mouseScroll(osgGA::GUIEventAdapter::SCROLL_UP);
	else
		m_pEventQueue->mouseScroll(osgGA::GUIEventAdapter::SCROLL_DOWN);
	update();
}

void OSGView::keyPressEvent(QKeyEvent *event)
{
	const std::string text = event->text().toStdString();
	auto sss = event->text().toLatin1().data();
	osgGA::GUIEventAdapter::KeySymbol keySymbol = (osgGA::GUIEventAdapter::KeySymbol)text[0];
	m_pEventQueue->keyPress(keySymbol);
	update();
}

void OSGView::keyReleaseEvent(QKeyEvent *event)
{
	const std::string text = event->text().toStdString();
	if (text.size() == 1)
	{
		m_pEventQueue->keyRelease(text[0]);
		update();
	}
}