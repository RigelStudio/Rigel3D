/*************************************************
 // Copyright(C)  MEEngine Team
 // File name:    GeometryFloor
 // Author:       Simon       
 // Version:      1.0     
 // Date:         2017/05/11
 // Description:  一个地面
 //	History:
 *************************************************/
#ifndef GEOMETRYFLOOR_H
#define GEOMETRYFLOOR_H

#include "Export.h"
#include <windows.h>
#include <osg/Geode>
#include <osg/Geometry>

class GEOMETRY_EXPORT GeometryFloor : public osg::Geode
{
public:
	GeometryFloor(size_t lenght = 50, size_t width = 50);
	virtual ~GeometryFloor(void);

	void setTexture(std::string image);

private:
	void createFloor(size_t lenght, size_t width);

	osg::Geometry* createPlane(size_t lenght, size_t width);
};

#endif // GEOMETRYFLOOR_H
