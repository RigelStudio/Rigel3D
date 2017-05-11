/*************************************************
// Copyright(C) MEEngine Team
// File name:    Core.h
// Author:       冯亚
// Version:      1.0
// Date:         2017-5-11
// Description:  
//	History:
*************************************************/
#ifndef MODELEDIT_CORE_H
#define MODELEDIT_CORE_H
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

#endif // MODELEDIT_CORE_H
