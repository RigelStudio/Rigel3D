#include <SymbolTool/SymbolFence.h>

SymbolFence::SymbolFence(void)
{
	m_pCuboid = NULL;
	m_pPolygon = NULL;
	m_pCuboiding = NULL;
}

SymbolFence::~SymbolFence(void)
{
	m_pCuboid = NULL;
	m_pPolygon = NULL;
	m_pCuboiding = NULL;
}

void SymbolFence::init()
{
	m_pPolygon = new GeometryPolygon;
	m_pPolygon->setColor(osg::Vec4(1, 1, 1, 1));

	m_pCuboiding = new GeometryCuboid;
	m_pCuboiding->setColor(osg::Vec4(1, 1, 1, 1));
	m_pCuboiding->setWidth(m_numWidth);
	m_pCuboiding->setHeight(m_numHeight);
	m_pCuboiding->setTexture(m_strTexture);

	m_pCuboid = new GeometryCuboid;
	m_pCuboid->setColor(osg::Vec4(1, 1, 1, 1));
	m_pCuboid->setWidth(m_numWidth);
	m_pCuboid->setHeight(m_numHeight);
	m_pCuboid->setTexture(m_strTexture);

	m_pGeomGeode->addDrawable(m_pCuboid);
	m_pGeomGeode->addDrawable(m_pPolygon);
	m_pGeomGeode->addDrawable(m_pCuboiding);
}

void SymbolFence::clickEvent(osg::Vec3 pos)
{
	if (!m_isStart)
	{
		return;
	}
	if (pos == osg::Vec3())
	{
		return;
	}
	if (m_pCuboid != NULL)
	{
		m_pCuboid->addPoint(pos);
	}
}

void SymbolFence::moveEvent(osg::Vec3 pos)
{
	if (m_pTextInfo != NULL)
	{
		m_pTextInfo->setPosition(pos);
	}
	if (!m_isStart)
	{
		return;
	}
	if (m_pCuboiding != NULL)
	{
		m_pCuboiding->setPoint(0, m_pCuboid->lastPoint());
		m_pCuboiding->setPoint(1, pos);
	}
}

void SymbolFence::endDraw()
{
	m_pPolygon->setVertexs(m_pCuboid->getSouceArray());
	SymbolBase::endDraw();
	m_pGeomGeode->removeDrawable(m_pCuboiding);
	m_pCuboiding = NULL;
}
