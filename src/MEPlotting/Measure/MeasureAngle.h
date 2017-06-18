#ifndef MEASUREANGLE_H
#define MEASUREANGLE_H
#include <MeasureTool/MeasureBase.h>
#include <Geometry/GeometryLine.h>

class MeasureAngle : public MeasureBase
{
public:
	MeasureAngle(void);
	~MeasureAngle(void);

	void clickEvent(osg::Vec3 pos);

	void moveEvent(osg::Vec3 pos);

	float calcResult();

	void endMeasure();
private:
	void init();

private:
	osg::ref_ptr<GeometryLine> m_pMainLine;
};

#endif//MEASUREANGLE_H