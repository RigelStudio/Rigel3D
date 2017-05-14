#ifndef GEOMETRYPOLYGON_H
#define GEOMETRYPOLYGON_H
#include "Export.h"
#include <Geometry/GeometryBase.h>
#include <Geometry/Style.h>

class GEOMETRY_EXPORT GeometryPolygon : public GeometryBase, public StyleBase
{
public:
	GeometryPolygon(void);
	~GeometryPolygon(void);

	void updateStyle();

	void updateGeomtry();

};

#endif//GEOMETRYPOLYGON_H