#include "GeometryPipe.h"
#include <osg/PolygonOffset>
#include <osgUtil/Tessellator>
#include "RigelMath/MEMath.h"

GeometryPipe::GeometryPipe()
{
	setName("GeometryPipe");
	setDataVariance(Object::DYNAMIC);
	m_numParts = 18;
}


GeometryPipe::GeometryPipe(osg::Vec3Array* points)
{
	setName("GeometryPipe");
	setDataVariance(Object::DYNAMIC);
	m_numParts = 18;
	m_pSouceArray = points;
	updateGeomtry();
}

GeometryPipe::~GeometryPipe()
{
}

void GeometryPipe::updateStyle()
{
	m_pColorArray->push_back(m_color);
	setColorBinding(Geometry::BIND_OVERALL);
	m_pStateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF |
		osg::StateAttribute::OVERRIDE);
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
		osg::PrimitiveSet::TRIANGLE_STRIP, 0, m_pVertexArray->size()));
	m_pVertexArray->dirty();
}

void GeometryPipe::createPipe()
{
	auto curve = new osg::Vec3Array;
	curve = MEMath::BezierCurve(m_pSouceArray, m_numWidth * 30, 8);
	auto count = curve->size();
	interpolationCicle(curve);
	clacIndex(count);
	m_pTextureArray = MEMath::calcPipeTexCoord(curve, m_numParts);
 }

void GeometryPipe::interpolationCicle(const osg::Vec3Array* curve)
{
	m_pSouceArray->clear();
	osg::ref_ptr<osg::Vec3Array> circle = nullptr;
	osg::Vec3 lastDir, nextDir;

	size_t cout = curve->size();
	for (int i = 0; i < cout; i++)
	{
		osg::Vec3 dir = osg::Z_AXIS;
		if (i == 0)
		{
			dir = curve->at(i + 1) - curve->at(i);
		}
		else if (i == cout - 1)
		{
			dir = curve->at(i) - curve->at(i - 1);
		}
		else
		{
			lastDir = curve->at(i) - curve->at(i - 1);
			nextDir = curve->at(i + 1) - curve->at(i);
			dir = nextDir + lastDir;
		}
		dir.normalize();
		circle = MEMath::createCircle(curve->at(i), 1, dir, m_numParts);
		auto iter = m_pSouceArray->end();
		m_pSouceArray->insert(iter, circle->begin(), circle->end());
		circle.release();
	}
}

void GeometryPipe::clacIndex(int count)
{
	//外层循环控制拐点的遍历
	for (size_t i = 0; i < m_numParts; i++)
	{
		bool mod = i % 2; //判断是否单数行
		size_t index = -1;
 		if (mod)
		{
			//奇数行
			for (int j = count - 1; j >= 0; j--)
			{
				index = j*m_numParts + i; //第一行
				m_pVertexArray->push_back(m_pSouceArray->at(index));
				index = j*m_numParts + i + 1;		//第二行	
				if (i == m_numParts - 1)
				{
					index = j*m_numParts;
				}
				m_pVertexArray->push_back(m_pSouceArray->at(index));
			}
		}
		else
		{
			//偶数行
			for (size_t j = 0; j < count; j++)
			{
				index = j*m_numParts + i; //第一行
				m_pVertexArray->push_back(m_pSouceArray->at(index));

				index = j*m_numParts + i + 1;//第二行	
				if (i == m_numParts - 1)
				{
					index = j*m_numParts;
				}
				m_pVertexArray->push_back(m_pSouceArray->at(index));
			}
		}
	}
}

