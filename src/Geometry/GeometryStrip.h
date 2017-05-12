#ifndef GEOMETRYSTRIP_H
#define GEOMETRYSTRIP_H

#include "Export.h"
#include <Geometry/Style.h>
#include <Geometry/GeometryBase.h>
#include <osg/Array>

class GEOMETRY_EXPORT GeometryStrip : public GeometryBase, public StyleBase
{
public:
	GeometryStrip(void);

	GeometryStrip(osg::Vec3Array* vertexs);

	virtual ~GeometryStrip(void);

private:
	void updateStyle();

	void updateGeomtry();

	void createStrip();

private:
	osg::ref_ptr<osg::Vec3Array> m_pLefts;
	osg::ref_ptr<osg::Vec3Array> m_pRights;
	osg::ref_ptr<osg::Vec3Array> m_pTempArray;
};

#endif//GEOMETRYSTRIP_H