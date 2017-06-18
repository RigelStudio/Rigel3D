#include <SymbolTool\SymbolStrip.h>

SymbolStrip::SymbolStrip(void)
{
	m_pStrip = NULL;
}

SymbolStrip::~SymbolStrip(void)
{
	if (m_pStrip != NULL)
	{
		m_pStrip = NULL;
	}
}

void SymbolStrip::init()
{
	m_pStrip = new GeometryStrip;
	m_pStrip->setColor(osg::Vec4(1, 1, 1, 1));
	m_pStrip->setTexture(m_strTexture);
	m_pGeomGeode->addDrawable(m_pStrip);
}

void SymbolStrip::clickEvent(osg::Vec3 pos)
{
	if (!m_isStart)
	{
		return;
	}
	if (pos == osg::Vec3())
	{
		return;
	}
	if (m_pStrip != NULL)
	{
		m_pStrip->setPoint(m_numVertexs, pos);
		m_numVertexs = m_pStrip->pointSize();
	}
}

void SymbolStrip::moveEvent(osg::Vec3 pos)
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
	if (m_pStrip != NULL)
	{
		m_pStrip->setPoint(m_numVertexs, pos);
	}
}

void SymbolStrip::endDraw()
{
	SymbolBase::endDraw();
	m_pStrip = NULL;
}
