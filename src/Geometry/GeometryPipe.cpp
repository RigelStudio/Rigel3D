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
	addPrimitiveSet(new osg::DrawArrays(
		osg::PrimitiveSet::TRIANGLE_FAN, 0, m_pVertexArray->size()));
	m_pVertexArray->dirty();
}

void GeometryPipe::createPipe()
{
	size_t cout = m_pSouceArray->size();
	auto points = new osg::Vec3Array;
	int parts = 3;
	osg::ref_ptr<osg::Vec3Array> circle = nullptr;
	for (int i = 0; i < cout; i++)
	{
		osg::Vec3 dir = osg::Z_AXIS;
		if (i == cout - 1)
		{
			dir = m_pSouceArray->at(i) - m_pSouceArray->at(i - 1);
		}
		else
		{
			dir = m_pSouceArray->at(i + 1) - m_pSouceArray->at(i);
		}
		dir.normalize();
		circle = MEMath::createCircle(m_pSouceArray->at(i), 5, dir, parts);
		size_t part = circle->size();
		auto iter = points->end();
		points->insert(iter, circle->begin(), circle->end());
		//circle.release();
	}
 	//cout = points->size();
 	for (size_t i = 0; i < parts; i ++)
 	{
		for (size_t j = 0; j < cout; j ++)
		{
			size_t index = i + j*parts;
			m_pVertexArray->push_back(points->at(index));
		}
		if (i == parts - 1)
		{
			for (size_t j = 0; j < cout; j++)
			{
				size_t index = j*parts;
				m_pVertexArray->push_back(points->at(index));
			}
		}
 	}
 }
