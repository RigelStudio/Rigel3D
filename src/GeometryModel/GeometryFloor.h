/*************************************************
 // Copyright(C)  
 // File name:    GeometryFloor
 // Author:       冯亚       
 // Version:      1.0     
 // Date:         2017/05/10
 // Description:  一个地面
 //	History:
 *************************************************/
#ifndef GEOMETRYFLOOR_H
#define GEOMETRYFLOOR_H

#include "Export.h"
#include <windows.h>
#include <osg/Geode>
#include <osg/Geometry>

class GEOMETRYMODEL_EXPORT GeometryFloor : public osg::Geode
{
public:
	GeometryFloor(size_t lenght = 50, size_t width = 50);
	virtual ~GeometryFloor(void);

	void setTexture(std::string image);

private:
	void createFloor(size_t lenght, size_t width);

	osg::Geometry* createPlane(size_t lenght, size_t width);
};

#endif//GEOMETRYFLOOR_H