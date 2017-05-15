#include <Geometry/GeometryPolygon.h>
#include <osgUtil/Tessellator>
#include <osgUtil/DelaunayTriangulator>
#include <osg/PolygonOffset>

GeometryPolygon::GeometryPolygon(void)
{
	setName("GeometryPolygon");
}

GeometryPolygon::~GeometryPolygon(void)
{
}

void GeometryPolygon::updateStyle()
{
	m_pColorArray->push_back(m_color);
	setColorBinding(Geometry::BIND_OVERALL);
	m_pStateSet->setRenderBinDetails(10, "RenderBin");
	m_pStateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF |
		osg::StateAttribute::PROTECTED);
	m_pStateSet->setMode(GL_BLEND, osg::StateAttribute::ON |
		osg::StateAttribute::PROTECTED);
	osg::PolygonOffset *offset = new osg::PolygonOffset;
	offset->setFactor(1.0);
	offset->setUnits(1.0);
	m_pStateSet->setAttributeAndModes(offset);

}

void GeometryPolygon::updateGeomtry()
{
	m_pVertexArray->clear();
	if (m_pSouceArray->size() < 2)
	{
		return;
	}
	m_pVertexArray->insert(m_pVertexArray->begin(), m_pSouceArray->begin(), m_pSouceArray->end());
	m_pVertexArray->insert(m_pVertexArray->end(), *m_pSouceArray->begin());
	m_pTextureArray->clear();
	float size = this->getNumPrimitiveSets();
	removePrimitiveSet(0,size);
	setTexCoordArray(0, m_pTextureArray);
	osgUtil::Tessellator tessellator;
 	tessellator.retessellatePolygons(*this);
	addPrimitiveSet(new osg::DrawArrays(
		osg::PrimitiveSet::POLYGON, 0, m_pVertexArray->size()));
	m_pVertexArray->dirty();
}
