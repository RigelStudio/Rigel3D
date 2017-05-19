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
	//auto iter = m_pVertexArray->end();
	//m_pSouceArray = MEMath::BezierCurve(m_pSouceArray, 5, 10);
	//m_pVertexArray->insert(iter, m_pSouceArray->begin(), m_pSouceArray->end());
	setTexCoordArray(0, m_pTextureArray);
	addPrimitiveSet(new osg::DrawArrays(
		osg::PrimitiveSet::TRIANGLE_STRIP, 0, m_pVertexArray->size()));
	m_pVertexArray->dirty();
}

void GeometryPipe::createPipe()
{
	m_pSouceArray = MEMath::BezierCurve(m_pSouceArray, m_numWidth * 5, 20);
	auto points = new osg::Vec3Array;
	int parts = 10;
	osg::ref_ptr<osg::Vec3Array> circle = nullptr;
	osg::Vec3 lastDir, nextDir;

	size_t cout = m_pSouceArray->size();
	for (int i = 0; i < cout; i++)
	{
		osg::Vec3 dir = osg::Z_AXIS;
		if (i == 0)
		{
			dir = m_pSouceArray->at(i + 1) - m_pSouceArray->at(i);
		}
		else if (i == cout - 1)
		{
			dir = m_pSouceArray->at(i) - m_pSouceArray->at(i - 1);
		}
		else
		{
			lastDir = m_pSouceArray->at(i) - m_pSouceArray->at(i - 1);
			nextDir = m_pSouceArray->at(i + 1) - m_pSouceArray->at(i);
			dir = lastDir + nextDir;
		}
		dir.normalize();
		circle = MEMath::createCircle(m_pSouceArray->at(i), 5, dir, parts);
		size_t part = circle->size();
		auto iter = points->end();
		points->insert(iter, circle->begin(), circle->end());
		circle.release();
	}

	//外层循环控制拐点的遍历
	for (size_t i = 0; i < cout; i++)
	{
		//内层循环圆周的遍历
		if (i == 0)
		{
			for (size_t j = 0; j <= parts; j++)
			{
				size_t index = -1;
				if (j == parts)
				{
					index = i*parts;
					m_pVertexArray->push_back(points->at(index));
					index = (i + 1) * parts;
					m_pVertexArray->push_back(points->at(index));
					m_pVertexArray->push_back(points->at(index));
					continue;
				}
				index = i*parts + j;
				m_pVertexArray->push_back(points->at(index));
				index = (i + 1) * parts + j;
				m_pVertexArray->push_back(points->at(index));
			}
		}
		else if (i == cout - 1)
		{
			for (size_t j = 0; j <= parts; j++)
			{
				size_t index = -1;
				if (j == parts)
				{
					index = (i - 1) * parts;
					m_pVertexArray->push_back(points->at(index));
					index = i*parts;
					m_pVertexArray->push_back(points->at(index));
					continue;
				}
				index = (i - 1) * parts + j;
				m_pVertexArray->push_back(points->at(index));
				index = i*parts + j;
				m_pVertexArray->push_back(points->at(index));
			}
		}
		else
		{
			for (size_t j = 0; j <= parts; j++)
			{
				size_t index = -1;
				if (j == parts)
				{
					index = i*parts;
					m_pVertexArray->push_back(points->at(index));
					index = (i + 1) * parts;
					m_pVertexArray->push_back(points->at(index));
					continue;
				}
				index = i*parts + j;
				m_pVertexArray->push_back(points->at(index));
				m_pVertexArray->push_back(points->at(index));
				index = (i + 1) * parts + j;
				m_pVertexArray->push_back(points->at(index));
			}
		}

	}

	m_pTextureArray = MEMath::calcPipeTexCoord(m_pSouceArray, parts);
 }
