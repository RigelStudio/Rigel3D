#include "Core.h"

Core* Core::s_pSelf = nullptr;

Core* Core::ins()
{
	if (s_pSelf == nullptr)
	{
		s_pSelf = new Core;
	}
	return s_pSelf;
}

void Core::destory()
{
	if (s_pSelf == nullptr)
	{
		delete s_pSelf;
		s_pSelf = nullptr;
	}
}

void Core::init()
{
	if (m_pOsgView == nullptr)
	{
		m_pOsgView = new OSGGraphView;
		m_pGraphScene = new QGraphicsScene;
		m_pOsgView->setScene(m_pGraphScene);
	}
	m_pSceneData = new osg::Group;
	m_pOsgView->getViewer()->setSceneData(m_pSceneData);
}

OSGGraphView* Core::getOSGView()
{
	return m_pOsgView;
}

QGraphicsScene* Core::getGraphScene()
{
	return m_pGraphScene;
}

osgViewer::Viewer* Core::getViewer()
{
	return m_pOsgView->getViewer();
}

osg::Camera* Core::getCamera()
{
	return m_pOsgView->getViewer()->getCamera();
}

Core::Core()
{
	m_pOsgView = nullptr;
	m_pGraphScene = nullptr;
}

Core::~Core()
{
}
