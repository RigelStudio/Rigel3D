#ifndef GEOMETRYLINE_H
#define GEOMETRYLINE_H
#include "Export.h"
#include <RigelModel/GeometryBase.h>

class DLL_EXPORT GeometryLine : public GeometryBase , public StyleBase
{
public:
	GeometryLine(void);
	GeometryLine(osg::Vec3Array* array);
	~GeometryLine(void);

private:
	void updateStyle();

	void updateGeomtry();

};

#endif//GEOMETRYLINE_H