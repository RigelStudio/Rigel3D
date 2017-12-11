#include "Style.h"

StyleBase::StyleBase(void)
{
	m_numWidth = 1.0;
}

StyleBase::~StyleBase(void)
{
}

void StyleBase::setColor(const osg::Vec4 color)
{
	m_color = color;
	updateStyle();
}

void StyleBase::setWidth(float width)
{
	m_numWidth = width;
	updateStyle();
}

TextStyle::TextStyle()
{

}

TextStyle::~TextStyle()
{

}

void TextStyle::setFont(std::string filePath)
{
	m_strTextFont = filePath;
	updateStyle();
}

BoxStyle::BoxStyle(void)
{
	m_numHeight = 3.0;
}

BoxStyle::~BoxStyle(void)
{
}

void BoxStyle::setHeight(float height)
{
	m_numHeight = height;
	updateStyle();
}

void BoxStyle::setLenth(float length)
{
	m_numLength = length;
	updateStyle();
}
