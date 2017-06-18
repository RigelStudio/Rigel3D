#ifndef MEASUREMARKSPHERE_H
#define MEASUREMARKSPHERE_H
#include <MeasureTool/Export.h>
#include <osg/AutoTransform>
#include <osg/Shape>
#include <osg/Geode>
#include <osg/ShapeDrawable>
class MEASURE_EXPORT MeasureMarkSphere : public osg::Group
{
public:
	MeasureMarkSphere(void);
	~MeasureMarkSphere(void);

	void addMarkSphere(const osg::Vec3 pos);
};

#endif//MEASUREMARKSPHERE_H