#include<Geometry\GeometryStrip.h>
#include "MEMath\MEMath.h"
#include <osg/PolygonOffset>
#include <osgUtil/Tessellator>

GeometryStrip::GeometryStrip(void)
{
	m_numWidth = 5;
	m_pLefts = new osg::Vec3Array;
	m_pRights = new osg::Vec3Array;
	m_pTempArray = new osg::Vec3Array;
	setDataVariance(Object::DYNAMIC);
	setName("GeometryStrip");
}

GeometryStrip::GeometryStrip(osg::Vec3Array* vertexs)
{
	m_numWidth = 1;
	m_pLefts = new osg::Vec3Array;
	m_pRights = new osg::Vec3Array;
	m_pTempArray = new osg::Vec3Array;
	setDataVariance(Object::DYNAMIC);
	setName("GeometryStrip");
	m_pSouceArray = vertexs;
	updateGeomtry();
}

GeometryStrip::~GeometryStrip(void)
{
}

void GeometryStrip::updateStyle()
{
	m_pColorArray->push_back(m_color);
	setColorBinding(Geometry::BIND_OVERALL);
	m_pStateSet->setRenderBinDetails(10, "RenderBin");
	m_pStateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF |
		osg::StateAttribute::PROTECTED);
	m_pStateSet->setMode(GL_BLEND, osg::StateAttribute::OFF |
		osg::StateAttribute::PROTECTED);
	osg::PolygonOffset *offset = new osg::PolygonOffset;
	offset->setFactor(-1.0);
	offset->setUnits(-1.0);
	m_pStateSet->setAttributeAndModes(offset);
}

void GeometryStrip::updateGeomtry()
{
 	m_pTextureArray->clear();
 	float size = this->getNumPrimitiveSets();
 	removePrimitiveSet(0,size);
 	createStrip();
 	//m_pTextureArray = STMath::computePolygonTexCoord(m_pVertexArray, 1);
 	setTexCoordArray(0, m_pTextureArray);
// 	osgUtil::Tessellator tessellator;
// 	//tessellator.retessellatePolygons(*this);
 	addPrimitiveSet(new osg::DrawArrays(
 		osg::PrimitiveSet::TRIANGLE_STRIP, 0, m_pVertexArray->size()));
 	m_pVertexArray->dirty();
}

void GeometryStrip::createStrip()
{
	//每次压入顶点数组最后一个点
	size_t sizeV = m_pSouceArray->size();
	if (sizeV < 2)
	{
		return;
	}
 	m_pLefts->clear();
 	m_pRights->clear();
  	m_pVertexArray->clear();
  	m_pTextureArray->clear();
  	m_pNormalArray->clear();
 	MEMath::createStrip(m_numWidth, m_pSouceArray, m_pLefts, m_pRights);
	size_t countL = m_pRights->size();
	float _lenght = 0.0;
	for (size_t i = 0; i < countL; i++)
	{
		if (i == 0)
		{
			m_pVertexArray->push_back(m_pLefts->at(i));
			m_pTextureArray->push_back(osg::Vec2(0, 1));

			m_pVertexArray->push_back(m_pRights->at(i));
			m_pTextureArray->push_back(osg::Vec2(0, 0));
		}
		else if (i < countL - 1)
		{
			auto _pos = m_pLefts->at(i + 1);
			_lenght = (_pos - m_pLefts->at(i)).length();

			m_pVertexArray->push_back(m_pLefts->at(i));
			m_pTextureArray->push_back(osg::Vec2(_lenght, 1));

			_pos = m_pRights->at(i + 1);
			_lenght = (_pos - m_pRights->at(i)).length();
			m_pVertexArray->push_back(m_pRights->at(i));
			m_pTextureArray->push_back(osg::Vec2(_lenght, 0));
		}
		else
		{
			m_pVertexArray->push_back(m_pLefts->at(i));
			m_pTextureArray->push_back(osg::Vec2(1, 1));

			m_pVertexArray->push_back(m_pRights->at(i));
			m_pTextureArray->push_back(osg::Vec2(1, 0));
		}
		
		m_pNormalArray->push_back(osg::Z_AXIS);
		m_pNormalArray->push_back(osg::Z_AXIS);
	}
	
}
