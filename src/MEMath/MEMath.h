#ifndef MEMATH_H
#define MEMATH_H
#include "Export.h"
#include <osg/Vec3>
#include <osg/Array>

class MECORE_EXPORT MEMath
{
public:
	MEMath();
	~MEMath();

	//计算一系列折线段的总长度
	static float getLength(osg::Vec3Array* source);

	//判断线段AB, CD是否相交，交点是参数5;
	inline static bool intersect(osg::Vec3 posA, osg::Vec3 posB,
		osg::Vec3 posC, osg::Vec3 posD, osg::Vec3& posInter);

	//创建一个面带,入参是面带的宽度和中点的数组;返回值分成左边的点（参数3）和右边的点（参数4）
	static bool createStrip(float radius, osg::Vec3Array* source, 
		osg::Vec3Array* lefts, osg::Vec3Array* rights);
};

#endif//MEMATH_H