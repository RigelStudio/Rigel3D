#ifndef GEOMETRYPIPE_H
#define GEOMETRYPIPE_H

#include "Export.h"
#include "GeometryBase.h"

class DLL_EXPORT GeometryPipe: public GeometryBase, public StyleBase
{
public:
	GeometryPipe();
	GeometryPipe(osg::Vec3Array* points);
	~GeometryPipe();

private:
	void updateStyle();

	void updateGeomtry();
	
	void createPipe();

	//通过曲线插值圆周
	void interpolationCicle(const osg::Vec3Array* curve);

	//根据曲线计算顶点索引
	void clacIndex(int count);

private:
	int  m_numParts; //圆周插值分段数
	osg::ref_ptr<osg::UIntArray> m_pIndexs;
};

#endif//GEOMETRYPIPE_H