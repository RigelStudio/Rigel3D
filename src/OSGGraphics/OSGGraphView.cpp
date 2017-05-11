#include "OSGGraphView.h"
#include <QPaintEngine>

OSGGraphView::OSGGraphView()
{
	m_pOSGWidget = new OSGWidget;
	m_pGraphWindow = m_pOSGWidget->getGraphicsWindow();
	setViewport(m_pOSGWidget);
	setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
}

OSGGraphView::~OSGGraphView()
{

}

osgViewer::Viewer* OSGGraphView::getViewer()
{
	return m_pOSGWidget->m_pViewer;
}

bool OSGGraphView::viewportEvent(QEvent* event)
{
	switch (event->type())
	{
	case QEvent::TouchBegin:
	{
		QList<QTouchEvent::TouchPoint> touchPoints = static_cast<QTouchEvent *>(event)->touchPoints();
		unsigned int id = 0;
		osg::ref_ptr<osgGA::GUIEventAdapter> osgEvent(NULL);
		foreach(const QTouchEvent::TouchPoint& touchPoint, touchPoints)
		{
			QList<QGraphicsItem*> listItems = items(mapToScene(touchPoint.pos().x(), touchPoint.pos().y()).toPoint());
			if (listItems.size() > 0)
			{
				return true;
			}
			unsigned int tap_count = touchPoints.size();
			if (!osgEvent)
			{
				osgEvent = m_pGraphWindow->getEventQueue()->touchBegan(id, osgGA::GUIEventAdapter::TOUCH_BEGAN, touchPoint.pos().x(), touchPoint.pos().y());
			}
			else
			{
				osgEvent->addTouchPoint(id, osgGA::GUIEventAdapter::TOUCH_BEGAN, touchPoint.pos().x(), touchPoint.pos().y());
			}
			id++;
		}
	}
	break;
	case QEvent::TouchEnd:
	{
		QList<QTouchEvent::TouchPoint> touchPoints = static_cast<QTouchEvent *>(event)->touchPoints();
		unsigned int id = 0;
		osg::ref_ptr<osgGA::GUIEventAdapter> osgEvent(NULL);
		foreach(const QTouchEvent::TouchPoint& touchPoint, touchPoints)
		{
			QList<QGraphicsItem*> listItems = items(mapToScene(touchPoint.pos().x(), touchPoint.pos().y()).toPoint());
			if (listItems.size() > 0)
			{
				return true;
			}
			unsigned int tap_count = touchPoints.size();
			if (!osgEvent)
			{
				osgEvent = m_pGraphWindow->getEventQueue()->touchEnded(id, osgGA::GUIEventAdapter::TOUCH_ENDED, touchPoint.pos().x(), touchPoint.pos().y(), tap_count);
			}
			else
			{
				osgEvent->addTouchPoint(id, osgGA::GUIEventAdapter::TOUCH_ENDED, touchPoint.pos().x(), touchPoint.pos().y());
			}
			id++;
		}
	}
	break;
	case QEvent::TouchUpdate:
	{
		QList<QTouchEvent::TouchPoint> touchPoints = static_cast<QTouchEvent *>(event)->touchPoints();
		unsigned int id = 0;
		osg::ref_ptr<osgGA::GUIEventAdapter> osgEvent(NULL);
		foreach(const QTouchEvent::TouchPoint& touchPoint, touchPoints)
		{
			QList<QGraphicsItem*> listItems = items(mapToScene(touchPoint.pos().x(), touchPoint.pos().y()).toPoint());
			if (listItems.size() > 0)
			{
				return true;
			}
			unsigned int tap_count = touchPoints.size();
			if (!osgEvent)
			{
				osgEvent = m_pGraphWindow->getEventQueue()->touchMoved(id, osgGA::GUIEventAdapter::TOUCH_MOVED, touchPoint.pos().x(), touchPoint.pos().y());
			}
			else
			{
				osgEvent->addTouchPoint(id, osgGA::GUIEventAdapter::TOUCH_MOVED, touchPoint.pos().x(), touchPoint.pos().y());
			}
			id++;
		}
	}
	break;
	default:
		return QGraphicsView::viewportEvent(event);
	}
	return true;
}

void OSGGraphView::setKeyboardModifiers(QInputEvent* event)
{
	int modkey = event->modifiers() & (Qt::ShiftModifier | Qt::ControlModifier | Qt::AltModifier);
	unsigned int mask = 0;
	if (modkey & Qt::ShiftModifier) mask |= osgGA::GUIEventAdapter::MODKEY_SHIFT;
	if (modkey & Qt::ControlModifier) mask |= osgGA::GUIEventAdapter::MODKEY_CTRL;
	if (modkey & Qt::AltModifier) mask |= osgGA::GUIEventAdapter::MODKEY_ALT;

	m_pGraphWindow->getEventQueue()->getCurrentEventState()->setModKeyMask(mask);
}

void OSGGraphView::keyPressEvent(QKeyEvent* event)
{
	QPoint pos = QCursor::pos();
	QList<QGraphicsItem*> listItems = items(mapToScene(pos.x(), pos.y()).toPoint());
	if (listItems.size() <= 0)
	{
		setKeyboardModifiers(event);
		m_pGraphWindow->getEventQueue()->keyPress(
			(osgGA::GUIEventAdapter::KeySymbol)*(event->text().toLatin1().data()));
	}
	QGraphicsView::keyPressEvent(event);
}

void OSGGraphView::keyReleaseEvent(QKeyEvent* event)
{
	setKeyboardModifiers(event);
	m_pGraphWindow->getEventQueue()->keyRelease(
		(osgGA::GUIEventAdapter::KeySymbol)*(event->text().toLatin1().data()));

	QGraphicsView::keyReleaseEvent(event);
}

void OSGGraphView::mousePressEvent(QMouseEvent* event)
{
	QPoint pos = event->pos();
	QList<QGraphicsItem*> listItems = items(mapToScene(pos.x(), pos.y()).toPoint());
	if (listItems.size() > 0)
	{
		QGraphicsView::mousePressEvent(event);
	}
	else
	{
		int button = 0;
		switch (event->button())
		{
		case Qt::LeftButton: button = 1; break;
		case Qt::MidButton: button = 2; break;
		case Qt::RightButton: button = 3; break;
		case Qt::NoButton: button = 0; break;
		default: button = 0; break;
		}
		setKeyboardModifiers(event);
		m_pGraphWindow->getEventQueue()->mouseButtonPress(event->x(), event->y(), button);
	}
}

void OSGGraphView::mouseReleaseEvent(QMouseEvent* event)
{
	int button = 0;
	switch (event->button())
	{
	case Qt::LeftButton: button = 1; break;
	case Qt::MidButton: button = 2; break;
	case Qt::RightButton: button = 3; break;
	case Qt::NoButton: button = 0; break;
	default: button = 0; break;
	}
	setKeyboardModifiers(event);
	m_pGraphWindow->getEventQueue()->mouseButtonRelease(event->x(), event->y(), button);

	QGraphicsView::mouseReleaseEvent(event);
}

void OSGGraphView::mouseDoubleClickEvent(QMouseEvent* event)
{
	QPoint pos = QCursor::pos();
	QList<QGraphicsItem*> listItems = items(mapToScene(pos.x(), pos.y()).toPoint());
	if (listItems.size() > 0)
	{
		return;
	}
	int button = 0;
	switch (event->button())
	{
	case Qt::LeftButton: button = 1; break;
	case Qt::MidButton: button = 2; break;
	case Qt::RightButton: button = 3; break;
	case Qt::NoButton: button = 0; break;
	default: button = 0; break;
	}
	setKeyboardModifiers(event);
	m_pGraphWindow->getEventQueue()->mouseDoubleButtonPress(event->x(), event->y(), button);

	QGraphicsView::mouseDoubleClickEvent(event);
}

void OSGGraphView::mouseMoveEvent(QMouseEvent* event)
{
	setKeyboardModifiers(event);
	m_pGraphWindow->getEventQueue()->mouseMotion(event->x(), event->y());
	QGraphicsView::mouseMoveEvent(event);
}

void OSGGraphView::wheelEvent(QWheelEvent* event)
{
	setKeyboardModifiers(event);
	m_pGraphWindow->getEventQueue()->mouseScroll(
		event->orientation() == Qt::Vertical ?
		(event->delta() > 0 ? osgGA::GUIEventAdapter::SCROLL_UP : osgGA::GUIEventAdapter::SCROLL_DOWN) :
		(event->delta() > 0 ? osgGA::GUIEventAdapter::SCROLL_LEFT : osgGA::GUIEventAdapter::SCROLL_RIGHT));
	QGraphicsView::wheelEvent(event);
}

void OSGGraphView::resizeEvent(QResizeEvent *event)
{
	if (scene())
	{
		scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
	}

	const QSize& size = event->size();
	m_pGraphWindow->resized(x(), y(), size.width(), size.height());
	m_pGraphWindow->getEventQueue()->windowResize(x(), y(), size.width(), size.height());
	m_pGraphWindow->requestRedraw();
	QGraphicsView::resizeEvent(event);
}

void OSGGraphView::moveEvent(QMoveEvent* event)
{
	const QPoint& pos = event->pos();
	m_pGraphWindow->resized(pos.x(), pos.y(), width(), height());
	m_pGraphWindow->getEventQueue()->windowResize(pos.x(), pos.y(), width(), height());

	QGraphicsView::moveEvent(event);
}

void OSGGraphView::timerEvent(QTimerEvent *event)
{
	scene()->update();
}
