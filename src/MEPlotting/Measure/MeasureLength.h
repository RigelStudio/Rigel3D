#ifndef MEASURELENGTH_H
#define MEASURELENGTH_H
#include "Export.h"
#include "MeasureBase.h"
#include <Geometry/GeometryLine.h>

class MeasureLength : public MeasureBase
{
public:
	MeasureLength(void);
	~MeasureLength(void);

	void clickEvent(osg::Vec3 pos);

	void moveEvent(osg::Vec3 pos);

	float calcResult();

	void endMeasure();
private:
	void init();

private:
	osg::ref_ptr<GeometryLine> m_pMainLine;
};

#endif//MEASURELENGTH_H
