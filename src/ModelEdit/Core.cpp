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

void Core::init(GraphicsView* osgView)
{
	if (osgView)
	{
		m_pOsgView = osgView;
		m_pGraphScene = m_pOsgView->scene();
		m_pViewer = m_pOsgView->getOSGViewer();
		m_pSceneData = m_pOsgView->getRoot();
	}
}


GraphicsView* Core::getOSGView()
{
	return m_pOsgView;
}

QGraphicsScene* Core::getGraphScene()
{
	return m_pGraphScene;
}

osgViewer::Viewer* Core::getViewer()
{
	return m_pOsgView->getOSGViewer();
}

osg::Camera* Core::getCamera()
{
	return m_pOsgView->getOSGViewer()->getCamera();
}

osg::Group* Core::getSceneData()
{
	return m_pSceneData;
}

osgGA::CameraManipulator* Core::getManipulator()
{
	return m_pViewer->getCameraManipulator();
}

Core::Core()
{
	m_pViewer = nullptr;
	m_pOsgView = nullptr;
	m_pGraphScene = nullptr;
}

Core::~Core()
{
}
