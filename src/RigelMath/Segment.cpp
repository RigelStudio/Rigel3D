#include "Segment.h"

Segment::Segment(osg::Vec3 start, osg::Vec3 end)
	:m_startPos(start), m_endPos(end)
{

}


Segment::Segment()
{

}

Segment::~Segment()
{
}

osg::Vec3 Segment::dir()
{
	auto _dir = m_endPos - m_startPos;
	_dir.normalize();
	return _dir;
}

osg::Vec3 Segment::vector()
{
	auto _dir = m_endPos - m_startPos;
	return _dir;
}

float Segment::length()
{
	auto _dir = m_endPos - m_startPos;;
	return _dir.length();
}

void Segment::setStart(const osg::Vec3& start)
{
	m_startPos = start;
}

void Segment::setEnd(const osg::Vec3& end)
{
	m_endPos = end;
}
