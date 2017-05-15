#include<Geometry\GeometryStrip.h>
#include "MEMath\MEMath.h"
#include <osg/PolygonOffset>
#include <osgUtil/Tessellator>
#include <iostream>

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
	m_numWidth = 1.5;
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
	m_pStateSet->setMode(GL_BLEND, osg::StateAttribute::ON |
		osg::StateAttribute::OVERRIDE);
	osg::PolygonOffset *offset = new osg::PolygonOffset;
	offset->setFactor(1.0);
	offset->setUnits(1.0);
	m_pStateSet->setAttributeAndModes(offset);
}

void GeometryStrip::updateGeomtry()
{
 	m_pTextureArray->clear();
 	float size = this->getNumPrimitiveSets();
 	removePrimitiveSet(0,size);
 	createStrip();
 	setTexCoordArray(0, m_pTextureArray);
 	//osgUtil::Tessellator tessellator;
 //	tessellator.retessellatePolygons(*this);
 	addPrimitiveSet(new osg::DrawArrays(
 		osg::PrimitiveSet::LINE_STRIP, 0, m_pVertexArray->size()));
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
 	MEMath::createStripRound(m_numWidth, m_pSouceArray, m_pLefts, m_pRights);
	m_pRights = MEMath::BezierCurve(m_pRights, 1.0);
	m_pLefts = MEMath::BezierCurve(m_pLefts, 1.0);
	
	float _lenghtL = MEMath::getLength(m_pLefts);
	float _lenghtR = MEMath::getLength(m_pRights);
	
	float theL = 0.0;
	float theR = 0.0;
	
	size_t countR = m_pRights->size();
	for (size_t i = 0; i < countR; i++)
	{
		if (i == 0)
		{
			m_pVertexArray->push_back(m_pRights->at(i));
			m_pTextureArray->push_back(osg::Vec2(0, 0));

			//m_pVertexArray->push_back(m_pLefts->at(i));
			m_pTextureArray->push_back(osg::Vec2(0, 1));
		}
		else if (i < countR - 1)
		{

			auto _pos = m_pRights->at(i);
			theR += (_pos - m_pRights->at(i - 1)).length();
			m_pVertexArray->push_back(m_pRights->at(i));
			m_pTextureArray->push_back(osg::Vec2(theR /10.0, 0));

			_pos = m_pLefts->at(i);
			theL += (_pos - m_pLefts->at(i - 1)).length();
			//m_pVertexArray->push_back(m_pLefts->at(i));
			m_pTextureArray->push_back(osg::Vec2(theL / 10.0, 1));
		}
		else
		{
			m_pVertexArray->push_back(m_pRights->at(i));
			m_pTextureArray->push_back(osg::Vec2(_lenghtR /10, 0));

			//m_pVertexArray->push_back(m_pLefts->at(i));
			m_pTextureArray->push_back(osg::Vec2(_lenghtL / 10.0, 1));
		}
		m_pNormalArray->push_back(osg::Z_AXIS);
		m_pNormalArray->push_back(osg::Z_AXIS);
	}
}