#ifndef POSPICKHANDLER_H
#define POSPICKHANDLER_H

#include <osgGA/GUIEventHandler>
#include <osgGA/GUIActionAdapter>
#include "MECore/SigSlot.h"
#include "MECore/SigSlot.h"

class PosPickHandler : public osgGA::GUIEventHandler
{
public:
	PosPickHandler();
	~PosPickHandler();

	void setEnable(bool isEnable);
	bool isEnable() { return m_isEnable; }

private:
	bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	osg::Vec3 pickPos(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

public:
	void signalPos(osg::Vec3 pos);

private:
	Signal<osg::Vec3> sig_Pos;
	bool m_isEnable;
	osg::Vec3 m_pushPos;
};

#endif//POSPICKHANDLER_H
