#ifndef GEOMETRYBASE_H
#define GEOMETRYBASE_H

#include "Export.h"
#include <osg/Geometry>
#include <osg/Texture2D>
#include <Geometry/Style.h>

class GEOMETRY_EXPORT GeometryBase : public osg::Geometry
{
public:
	GeometryBase(void);
	~GeometryBase(void);

	void addPoint(const osg::Vec3 &pos);

	void setPoint(size_t index, const osg::Vec3 &pos);
	
	void setVertexs(osg::Vec3Array* array);
	
	osg::Vec3Array* getSouceArray();

	size_t pointSize();

	osg::Vec3 atPoint(size_t index);
	
	osg::Vec3Array* getPoints(){ return m_pVertexArray; }
	//第一个顶点;
	virtual osg::Vec3 firstPoint();

	//最后一个顶点;
	virtual osg::Vec3 lastPoint();

	virtual void setTexture(std::string path);

protected:

	void init();
	
	virtual void updateGeomtry() = 0;

protected:
	bool m_isTransparent;
	osg::ref_ptr<osg::StateSet> m_pStateSet;
	osg::ref_ptr<osg::Vec3Array> m_pVertexArray;
	osg::ref_ptr<osg::Vec4Array> m_pColorArray;
	osg::ref_ptr<osg::Vec3Array> m_pNormalArray;
	osg::ref_ptr<osg::Vec2Array> m_pTextureArray;
	osg::ref_ptr<osg::Vec3Array> m_pSouceArray;
	osg::ref_ptr<osg::Texture2D> m_pTexture2D;
};

#endif//GEOMETRYBASE_H