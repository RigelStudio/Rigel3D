#include <SymbolTool/SymbolCuboid.h>
#include "windows.h"

SymbolCuboid::SymbolCuboid(void)
{
	m_pArray = NULL;
	m_pCuboid = NULL;
	m_pArray = new osg::Vec3Array;
}

SymbolCuboid::~SymbolCuboid(void)
{
}

void SymbolCuboid::setTexture(std::string &imagePath)
{
	m_strTexture = imagePath;
}

void SymbolCuboid::init()
{
	m_pCuboid = new GeometryCuboid;
	m_pCuboid->setColor(osg::Vec4(1, 1, 1, 1));
	m_pCuboid->setWidth(m_numWidth);
	m_pCuboid->setHeight(m_numHeight);
	m_pCuboid->setTexture(m_strTexture);
	m_pGeomGeode->addDrawable(m_pCuboid);
}

void SymbolCuboid::clickEvent(osg::Vec3 pos)
{
	if (!m_isStart)
	{
		return;
	}
	;
	if (pos.length() < 1.0)
	{
		return;
	}

	if (m_pCuboid != NULL)
	{
		m_pCuboid->addPoint(pos);
		m_pArray->push_back(pos);
	}
}

void SymbolCuboid::moveEvent(osg::Vec3 pos)
{
	if (pos.length() < 1.0)
	{
		return;
	}
	if (m_pTextInfo != NULL)
	{
		m_pTextInfo->setPosition(pos);
		m_pTextInfo->setText(L"ÓÒ¼ü½áÊø");
	}
	if (!m_isStart)
	{
		return;
	}
	if (m_pCuboid != NULL)
	{
		m_pCuboid->setPoint(m_pArray->size(), pos);
	}
}

void SymbolCuboid::endDraw()
{
	SymbolBase::endDraw();
	m_pCuboid = NULL;
	m_pArray->clear();
}
