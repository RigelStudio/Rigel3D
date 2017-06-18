#ifndef SYMBOLFENCE_H
#define SYMBOLFENCE_H

#include <osg/Array>
#include <SymbolTool/SymbolBase.h>
#include <Geometry/GeometryCuboid.h>
#include <Geometry/GeometryPolygon.h>

class SymbolFence : public SymbolBase
{
public:
	SymbolFence(void);
	virtual ~SymbolFence(void);

protected:
	void init();

	void clickEvent(osg::Vec3 pos);

	void moveEvent(osg::Vec3 pos);

	void endDraw();
private:
	osg::ref_ptr<GeometryCuboid> m_pCuboid;
	osg::ref_ptr<GeometryCuboid> m_pCuboiding;
	osg::ref_ptr<GeometryPolygon> m_pPolygon;
};

#endif//SYMBOLFENCE_H