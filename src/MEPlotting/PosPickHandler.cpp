#include "PosPickHandler.h"
#include <osgViewer/View>



PosPickHandler::PosPickHandler()
{
}


PosPickHandler::~PosPickHandler()
{
}

bool PosPickHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
	int keyMask = ea.getButtonMask();

	osg::Vec3 pos;
	switch (ea.getEventType())
	{
	case osgGA::GUIEventAdapter::DOUBLECLICK:
	{
		if (osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON == keyMask)
		{
			pos = pickPos(ea, aa);

		}
	}
	break;
	case osgGA::GUIEventAdapter::PUSH:
	{
		if (osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON == keyMask)
		{
			pos = pickPos(ea, aa);

		}
	}
	break;
	case osgGA::GUIEventAdapter::RELEASE:
	{
		pos = pickPos(ea, aa);

	}
	break;
	case osgGA::GUIEventAdapter::MOVE:
	{
		pos = pickPos(ea, aa);

	}
	break;
	default:
		break;
	}
	return false;
}

osg::Vec3 PosPickHandler::pickPos(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
	osg::Vec3 worldPos;
	osgViewer::View * view = dynamic_cast<osgViewer::View*>(&aa);
	if (NULL == view)
	{
		return worldPos;
	}
	
	osgUtil::LineSegmentIntersector::Intersections intersections;
	if (view->computeIntersections(ea.getX(), ea.getY(), intersections))
	{
		auto iter = intersections.begin();
		for (; iter != intersections.end(); iter++)
		{
			worldPos = iter->getWorldIntersectPoint();
			return worldPos;
		}
	}
	return worldPos;
}

void PosPickHandler::signalPos(osg::Vec3 pos)
{
	sig_Pos.emit(pos);
}

void PosPickHandler::setEnable(bool isEnable)
{
	m_isEnable = isEnable;
}
