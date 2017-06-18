#ifndef SYMBOLBASE_H
#define SYMBOLBASE_H

#include "Export.h"
#include <osg/Geode>
#include <osg/Group>
#include <string>

class SymbolBase : public osg::Group
{
public:
	SymbolBase(void);
	virtual ~SymbolBase(void);

protected:
	virtual void init();

	virtual void startDraw();

	virtual void endDraw();

	virtual void clickEvent(osg::Vec3 pos){};

	virtual void moveEvent(osg::Vec3 pos){};

protected:
	bool							m_isStart;
	float							m_numWidth;
	float							m_numHeight;
	size_t							m_numVertexs;
	bool							m_isUseText;
	std::string						m_strTexture;
	osg::ref_ptr<osg::Geode>		m_pGeomGeode;
};

#endif//SYMBOLBASE_H
