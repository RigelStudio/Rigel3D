/*************************************************
 // Copyright(C)  
 // File name:    OSGWidget
 // Author:       冯亚       
 // Version:      1.0     
 // Date:         2017/05/07
 // Description:  重写QGLWidget,以osg图形上下文来渲染
 //	History:
 *************************************************/
#ifndef OSGWIDGET_H
#define OSGWIDGET_H

#include "Export.h"
#include <QEvent>
#include <QTimer>
#include <QOpenGLWidget>
#include <osgViewer/Viewer>

class DLL_EXPORT OSGWidget : public QOpenGLWidget
{
public:
	OSGWidget(QWidget* parent = nullptr);
	~OSGWidget();

	void init();

	osg::Camera* createCamera(int x, int y, int w, int h);

	void setGraphicsWindow(osgViewer::GraphicsWindow* graphicsWindow);
	osgViewer::GraphicsWindow* getGraphicsWindow() { return m_pGraphicsWindow; };

private:
	virtual void paintGL();

	void resizeEvent(QResizeEvent *e);

public:
	QTimer m_timer;
	osgViewer::Viewer* m_pViewer;
	osgViewer::GraphicsWindow* m_pGraphicsWindow;
};

#endif//OSGWIDGET_H
