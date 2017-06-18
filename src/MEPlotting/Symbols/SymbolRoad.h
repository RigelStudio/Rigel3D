#ifndef SYMBOLPOLYGON_ROAD_H
#define SYMBOLPOLYGON_ROAD_H

#include <SymbolTool/SymbolBase.h>
#include <Geometry/GeometryLine.h>
#include <Geometry/GeometryPolygon.h>

class SymbolRoad : public SymbolBase
{
public:
	SymbolRoad(void);
	~SymbolRoad(void);

	void setTexture(std::string &imagePath);

protected:
	void init();

	void clickEvent(osg::Vec3 pos);

	void moveEvent(osg::Vec3 pos);

	void endDraw();
private:
	osg::ref_ptr<GeometryLine> m_pLine;
	osg::ref_ptr<osg::Geometry> _roadGeometry;
	osg::ref_ptr<osg::Vec3Array> _points;

protected:
};


#endif//SYMBOLPOLYGON_H