/*  	
 *@file   EventAdapter.h
 *@brief  brief  description  
 *@author louyk
 *@date   2015/05/17
 *@version 1.0.0
 *@note   采用QGraphicsView方式，把osg嵌入qt的绘制osg类
 */
#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H
#include <osgViewer/Viewer>
#include "EventAdapter.h"
#include "Export.h"

class DLL_EXPORT GraphicsView : public EventAdapter
{
	Q_OBJECT

public:
	GraphicsView(QWidget* parent = 0);
	~GraphicsView();

	osgViewer::Viewer* getOSGViewer(){ return m_pViewer; }
	osg::Group* getRoot(){ return m_pSceneData; }

protected:
	virtual void drawBackground(QPainter *painter, const QRectF& rect);
	virtual void timerEvent(QTimerEvent *event);

private:
	void init();

private:
	osg::Group* m_pSceneData;
	osgViewer::Viewer* m_pViewer;
};

#endif // GRAPHICSVIEW_H
