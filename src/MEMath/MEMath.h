#ifndef MEMATH_H
#define MEMATH_H
#include "Export.h"
#include <osg/Vec3>
#include <osg/Array>
#include "Segment.h"

class MECORE_EXPORT MEMath
{
	//定义类型: 线段
public:
	MEMath();
	~MEMath();

	//计算一系列折线段的总长度
	static float getLength(osg::Vec3Array* source);

	//判断线段AB, CD是否相交，交点是参数5;
	inline static bool intersectSegm(osg::Vec3 posA, osg::Vec3 posB,
		osg::Vec3 posC, osg::Vec3 posD, osg::Vec3& posInter);

	//判断直线AB, CD是否相交，交点是参数5;
	inline static bool intersectLine(osg::Vec3 posA1, osg::Vec3 posA2,
		osg::Vec3 posB1, osg::Vec3 posB2, osg::Vec3& posInter);

	//创建一个拐角为斜边的面带,入参是面带的宽度和中点的数组;返回值分成左边的点（参数3）和右边的点（参数4）
	static bool createStripBevel(float radius, osg::Vec3Array* source, 
		osg::Vec3Array* lefts, osg::Vec3Array* rights);

	//创建一个拐角为尖角的面带,入参是面带的宽度和中点的数组;返回值分成左边的点（参数3）和右边的点（参数4）
	static bool createStripMiter(float radius, osg::Vec3Array* source,
		osg::Vec3Array* lefts, osg::Vec3Array* rights);

	static osg::Vec2Array* clacStripTexCoord(osg::Vec3Array* source);

	//管线
	static osg::Vec3Array* createPipe(osg::Vec3Array* source, float radius);

	//贝塞尔曲线插值， 参数1：插值的数组，参数2：插值半径, 参数3：细分多少段
	static osg::Vec3Array* BezierCurve(osg::Vec3Array* vertexs, float radius, size_t parts);

	//创建一个圆周的数组， 参数1：圆心坐标， 参数2：半径，参数3：圆周分段数
	static osg::Vec3Array* createCircle(osg::Vec3 center, float radius, osg::Vec3 upDir, size_t parts = 10);
};

#endif//MEMATH_H