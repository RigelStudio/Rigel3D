#ifndef MEASUREHEIGHT_H
#define MEASUREHEIGHT_H
#include <MeasureTool/MeasureBase.h>
#include <Geometry/GeometryLine.h>

class MeasureHeight : public MeasureBase
{
public:
	MeasureHeight(void);
	~MeasureHeight(void);

	void clickEvent(osg::Vec3 pos);

	void moveEvent(osg::Vec3 pos);

	float calcResult();

	void endMeasure();
private:
	void init();

private:
	osg::ref_ptr<GeometryLine> m_pMainLine;
};

#endif//MEASUREHEIGHT_H