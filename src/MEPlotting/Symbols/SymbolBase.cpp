#include "SymbolBase.h"

SymbolBase::SymbolBase(void)
{
	m_isStart = false;
	m_numVertexs = 0;
	m_numWidth = 1.0;
	m_numHeight = 1.0;
	m_strTexture = "";
	m_pTextInfo = NULL;
	m_isUseText = true;
	m_pGeomGeode = new osg::Geode;
	addChild(m_pGeomGeode);
}
 
SymbolBase::~SymbolBase(void)
{
	removeChildren(0, getNumChildren());
}

void SymbolBase::startDraw()
{
	m_isStart = true;
	init();
	if (m_pTextInfo != NULL)
	{
		m_pTextInfo->setText(L"ÓÒ¼ü½áÊø»æÖÆ");
	}
	
}

void SymbolBase::endDraw()
{
	m_isStart = false;
	if (m_pTextInfo != NULL)
	{
		m_pTextInfo->setText(L"×ó¼üµã»÷»æÖÆ");
	}
}

void SymbolBase::setTexture(std::string &imagePath)
{
	m_strTexture = imagePath;
}

void SymbolBase::init()
{
	if (m_isUseText)
	{
		m_pTextInfo = new PlaceNode;
		m_pTextInfo->setText(L"×ó¼üµã»÷»æÖÆ");
		m_pTextInfo->setTextColor(osg::Vec4(0.8, 0, 0, 1));
		m_pTextInfo->setFontSize(15);
		m_pTextInfo->setTextPosition(osg::Vec3(0, 20,0));
		m_pTextInfo->setBackMode(LabelBase::FILL_BOX);
		m_pTextInfo->setBackColor(osg::Vec4(1, 1, 1, 0.5));
		addChild(m_pTextInfo);
	}
}

void SymbolBase::setWidth(float width)
{
	m_numWidth = width;
}

void SymbolBase::setHeight(float height)
{
	m_numHeight = height;
}

void SymbolBase::clearText()
{
	if (m_pTextInfo != NULL)
	{
		removeChild(m_pTextInfo);
		m_pTextInfo = NULL;
	}

}

void SymbolBase::setUseText(bool isUse)
{
	m_isUseText = isUse;
}
