#ifndef MEASUREAREA_H 
#define MEASUREAREA_H
#include <MeasureTool/MeasureBase.h>
#include <Geometry/GeometryPolygon.h>
#include <Geometry/GeometryLine.h>

class MeasureArea : public MeasureBase
{
public:
	MeasureArea(void);
	~MeasureArea(void);

	void clickEvent(osg::Vec3 pos);

	void moveEvent(osg::Vec3 pos);

	float calcResult();

	void endMeasure();
private:
	void init();

private:
	osg::ref_ptr<GeometryLine> m_pLine;
	osg::ref_ptr<GeometryPolygon> m_pPolygon;
};


#endif//MEASUREAREA_H