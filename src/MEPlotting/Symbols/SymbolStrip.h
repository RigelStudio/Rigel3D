#ifndef SYMBOLSTRIP_H
#define SYMBOLSTRIP_H

#include <SymbolTool/SymbolBase.h>
#include <Geometry/GeometryStrip.h>

class SymbolStrip : public SymbolBase
{
public:
	SymbolStrip(void);
	virtual ~SymbolStrip(void);

protected:
	void init();

	void clickEvent(osg::Vec3 pos);

	void moveEvent(osg::Vec3 pos);

	void endDraw();
private:
	osg::ref_ptr<GeometryStrip> m_pStrip;
};

#endif//SYMBOLSTRIP_H