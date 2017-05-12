#ifndef STYLE_H
#define STYLE_H
#include "Export.h"
#include <osg/Vec4>
#include <iostream>

class GEOMETRY_EXPORT StyleBase
{
public:
	StyleBase(void);
	~StyleBase(void);
	
	void setColor(const osg::Vec4 color);

	void setWidth(float width);

protected:
	virtual void updateStyle() = 0;

protected:
	float m_numWidth;
	osg::Vec4 m_color;
};

class TextStyle : public StyleBase
{
public:
	TextStyle();
	~TextStyle();

	void setFont(std::string filePath);

protected:
	std::string m_strTextFont;
};

class GEOMETRY_EXPORT BoxStyle : public StyleBase
{
public:
	BoxStyle(void);
	~BoxStyle(void);

	void setHeight(float height);
	
	void setLenth(float length);
protected:
	float m_numHeight;
	float m_numLength;
};

#endif//STYLE_H
