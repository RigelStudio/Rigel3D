/*************************************************
 // Copyright(C)  
 // File name:    OSGGraphView
 // Author:       冯亚       
 // Version:      1.0     
 // Date:         2017/05/07
 // Description:  重写QGraphicsView类，处理了多点触控的事件
 //	History:
 *************************************************/
#ifndef OSGGRAPHVIEW_H
#define OSGGRAPHVIEW_H
#include "Export.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QGraphicsView>
#include <QGLWidget>
#include <osgViewer/GraphicsWindow>

#include "OSGWidget.h"

class OSGWIDGET_EXPORT OSGGraphView : public QGraphicsView
{

public:
	OSGGraphView();
	~OSGGraphView();

	osgViewer::Viewer* getViewer();

protected:
	bool viewportEvent(QEvent* event);
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

public:
	OSGWidget* m_pOSGWidget;	//osg的渲染Widget
	osgViewer::GraphicsWindow* m_pGraphWindow;	//osgViewer的图形窗口
};

#endif // OSGGRAPHVIEW_H
