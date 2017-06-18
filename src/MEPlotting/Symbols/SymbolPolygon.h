#ifndef SYMBOLPOLYGON_H
#define SYMBOLPOLYGON_H

#include <SymbolTool/SymbolBase.h>
#include <Geometry/GeometryLine.h>
#include <Geometry/GeometryPolygon.h>

class SymbolPolygon : public SymbolBase
{
public:
	SymbolPolygon(void);
	~SymbolPolygon(void);

protected:
	void init();

	void clickEvent(osg::Vec3 pos);

	void moveEvent(osg::Vec3 pos);

	void endDraw();
private:
	osg::ref_ptr<GeometryLine> m_pLine;
	osg::ref_ptr<GeometryPolygon> m_pPolygon;
};


#endif//SYMBOLPOLYGON_H