#ifndef CORE_H
#define CORE_H

#include <QGraphicsScene>

#include <osg/Group>

#include "OSGGraphics/OSGGraphView.h"

class Core
{
public:
	static Core* ins();
	static void destory();

	//优先级最高的初始化
	void init();

	//
	OSGGraphView* getOSGView();

	QGraphicsScene* getGraphScene();

	osgViewer::Viewer* getViewer();

	osg::Camera* getCamera();

private:
	Core();
	~Core();

private:
	static Core* s_pSelf;
	OSGGraphView* m_pOsgView;
	QGraphicsScene* m_pGraphScene;
	osg::Group* m_pSceneData;
};

#endif//CORE_H
