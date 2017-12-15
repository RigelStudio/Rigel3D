#include "GeometryLine.h"
#include <osg/LineWidth>

GeometryLine::GeometryLine(void)
{
	setName("GeometryLine");
}

GeometryLine::GeometryLine(osg::Vec3Array* array)
{
	setName("GeometryLine");
	m_pSouceArray = array;
	updateStyle();
	updateGeomtry();
}

GeometryLine::~GeometryLine(void)
{
}

void GeometryLine::updateStyle()
{
	m_pColorArray->push_back(m_color);
	setColorBinding(Geometry::BIND_OVERALL);
// 	m_pNormalArray->push_back(osg::Z_AXIS);
// 	setNormalArray(m_pNormalArray, osg::Array::Binding::BIND_OVERALL);
	m_pStateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF |
		osg::StateAttribute::PROTECTED);
	m_pStateSet->setMode(GL_BLEND, osg::StateAttribute::ON |
		osg::StateAttribute::PROTECTED);
	m_pStateSet->setRenderBinDetails(10, "RenderBin");
	m_pStateSet->setAttributeAndModes(new osg::LineWidth(m_numWidth), osg::StateAttribute::ON);
}

void GeometryLine::updateGeomtry()
{
	m_pVertexArray = m_pSouceArray;
	float size = this->getNumPrimitiveSets();
	removePrimitiveSet(0, size);
	addPrimitiveSet(new osg::DrawArrays(
		osg::PrimitiveSet::LINES, 0, m_pVertexArray->size()));
	m_pVertexArray->dirty();
}

