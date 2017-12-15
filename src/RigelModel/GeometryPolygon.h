#ifndef GEOMETRYPOLYGON_H
#define GEOMETRYPOLYGON_H
#include "Export.h"
#include <RigelModel/GeometryBase.h>
#include <RigelModel/Style.h>

class DLL_EXPORT GeometryPolygon : public GeometryBase, public StyleBase
{
public:
	GeometryPolygon(void);
	~GeometryPolygon(void);

	void updateStyle();

	void updateGeomtry();

};

#endif//GEOMETRYPOLYGON_H