/*  	
 *@file   EventAdapter.h
 *@brief  brief  description  
 *@author louyk
 *@date   2015/05/17
 *@version 1.0.0
 *@note   采用QGraphicsView方式，把osg嵌入qt的事件处理类
 */
#ifndef EVENTADAPTER_H
#define EVENTADAPTER_H
#include <QInputEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QGraphicsView>
#include <osgViewer/GraphicsWindow>
#include "Export.h"

class DLL_EXPORT EventAdapter : public QGraphicsView
{
public:
	EventAdapter();
	~EventAdapter();

protected:
	//bool viewportEvent(QEvent* event);
	void setKeyboardModifiers(QInputEvent* event);
	virtual void keyPressEvent(QKeyEvent* event);
	virtual void keyReleaseEvent(QKeyEvent* event);
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
	virtual void mouseDoubleClickEvent(QMouseEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void wheelEvent(QWheelEvent* event);
	virtual void resizeEvent(QResizeEvent *event);
	virtual void moveEvent(QMoveEvent* event);
	virtual void timerEvent(QTimerEvent *event);

protected:
	osgViewer::GraphicsWindow* m_pGraphicsWindow;
};

#endif // EVENTADAPTER_H
