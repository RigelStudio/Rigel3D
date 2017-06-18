#include <SymbolTool\SymbolRoad.h>
#include <SymbolTool\RoadDrawer.h>
SymbolRoad::SymbolRoad(void)
{
// 	m_pPolygon = NULL;
	_points = new osg::Vec3Array;
}

SymbolRoad::~SymbolRoad(void)
{
}

void SymbolRoad::setTexture(std::string &imagePath)
{
	m_strTexture = imagePath;
}

void SymbolRoad::init()
{
	//SymbolBase::init();
// 	m_pPolygon = new GeometryPolygon;
// 	m_pPolygon->setColor(osg::Vec4(1, 1, 1, 1));
// 	m_pPolygon->setTexture(m_strTexture);

	m_pLine = new GeometryLine;
	m_pLine->setColor(osg::Vec4(0.5, 1, 1.0, 0.8));
	m_pLine->setWidth(3.0);
	m_pGeomGeode->addDrawable(m_pLine);
// 	m_pGeomGeode->addDrawable(m_pPolygon);
	
}

void SymbolRoad::clickEvent(osg::Vec3 pos)
{
	if (!m_isStart)
	{
		return;
	}
	if (pos == osg::Vec3())
	{
		return;
	}
	if (m_pLine != NULL)
	{
		m_pLine->addPoint(pos);
		_points->push_back(pos);
	}
// 	if (m_pPolygon != NULL)
// 	{
// 		m_pPolygon->addPoint(pos);
// 		m_numVertexs = m_pPolygon->pointSize();
// 	}
}

void SymbolRoad::moveEvent(osg::Vec3 pos)
{	
	if (pos == osg::Vec3())
	{
		return;
	}
	if (m_pTextInfo != NULL)
	{
		m_pTextInfo->setPosition(pos);
	}
	if (!m_isStart)
	{
		return;
	}
// 	if (m_pPolygon != NULL)
// 	{
// 		//m_pPolygon->setPoint(m_numVertexs, pos);
// 	}
	if (m_pLine != NULL)
	{
		m_pLine->setPoint(m_numVertexs, pos);
		m_pLine->setPoint(m_numVertexs + 1, m_pLine->firstPoint());
	}
}

void SymbolRoad::endDraw()
{
	SymbolBase::endDraw();
	_roadGeometry = QuadStripDrawer::Road(_points, 3, 3, 1, 1, 16);
	m_pGeomGeode->removeDrawable(m_pLine);
	m_pGeomGeode->removeDrawable(_roadGeometry);

}
