#include "MeasureBase.h"

MeasureBase::MeasureBase(void)
{
	m_numVertexs = 0;
	m_isStart = false;
	m_isEnd = false;
	m_strImagePath = "";
	m_pGeomGeode = NULL;
}

MeasureBase::~MeasureBase(void)
{
}

void MeasureBase::startMeasure()
{
	init();
}

void MeasureBase::endMeasure()
{
	m_isStart = false;
	m_isEnd = true;
}

void MeasureBase::clearTheMeasure(osg::Node* node)
{
	
}

void MeasureBase::setImagePath(std::string &imagePath)
{
	m_strImagePath = imagePath;
}

