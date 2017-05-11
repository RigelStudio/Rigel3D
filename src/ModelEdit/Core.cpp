#include "Core.h"
#include <osgGA/TrackballManipulator>

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
	m_pViewer = m_pOsgView->getViewer();
	m_pSceneData = new osg::Group;
	m_pViewer->setSceneData(m_pSceneData);
	auto* manipulator = new osgGA::TrackballManipulator;
	m_pViewer->setCameraManipulator(manipulator);
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
