#include "GeometryPipe.h"
#include <osg/PolygonOffset>
#include <osgUtil/Tessellator>
#include "MEMath/MEMath.h"

GeometryPipe::GeometryPipe()
{
	setName("GeometryPipe");
	setDataVariance(Object::DYNAMIC);
}


GeometryPipe::GeometryPipe(osg::Vec3Array* points)
{
	setName("GeometryPipe");
	setDataVariance(Object::DYNAMIC);
	m_pSouceArray = points;
	updateGeomtry();
}

GeometryPipe::~GeometryPipe()
{
}

void GeometryPipe::updateStyle()
{
	m_pColorArray->push_back(m_color);
	setWidth(2);
	setColorBinding(Geometry::BIND_OVERALL);
	m_pStateSet->setRenderBinDetails(10, "RenderBin");
	m_pStateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF |
		osg::StateAttribute::PROTECTED);
	m_pStateSet->setMode(GL_BLEND, osg::StateAttribute::ON |
		osg::StateAttribute::OVERRIDE);
	osg::PolygonOffset *offset = new osg::PolygonOffset;
	offset->setFactor(1.0);
	offset->setUnits(1.0);
	m_pStateSet->setAttributeAndModes(offset);
}

void GeometryPipe::updateGeomtry()
{
	m_pTextureArray->clear();
	float size = this->getNumPrimitiveSets();
	removePrimitiveSet(0, size);
	createPipe();
	setTexCoordArray(0, m_pTextureArray);
	//osgUtil::Tessellator tessellator;
	//	tessellator.retessellatePolygons(*this);
	addPrimitiveSet(new osg::DrawArrays(
		osg::PrimitiveSet::LINE_LOOP, 0, m_pVertexArray->size()));
	m_pVertexArray->dirty();
}

void GeometryPipe::createPipe()
{
	m_pVertexArray = MEMath::createPipe(m_pSouceArray, 5.0);
}
