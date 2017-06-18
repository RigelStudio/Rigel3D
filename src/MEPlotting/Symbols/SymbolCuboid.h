#ifndef SYMBOLCUBOID_H
#define SYMBOLCUBOID_H

#include <SymbolTool\SymbolBase.h>
#include <Geometry\GeometryCuboid.h>
#include <Geometry\GeometryLine.h>

class SymbolCuboid : public SymbolBase
{
public:
	SymbolCuboid(void);
	~SymbolCuboid(void);
	
	void setTexture(std::string &imagePath);
	
protected:
	void init();

	void clickEvent(osg::Vec3 pos);

	void moveEvent(osg::Vec3 pos);

	void endDraw();
	
private:
	osg::ref_ptr<GeometryCuboid> m_pCuboid;
	osg::ref_ptr<osg::Vec3Array> m_pArray;
};

#endif//SYMBOLCUBOID_H