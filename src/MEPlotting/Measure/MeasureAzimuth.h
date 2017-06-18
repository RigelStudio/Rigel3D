#include <MeasureTool/MeasureBase.h>
#include <Geometry/GeometryLine.h>

class MeasureAzimuth : public MeasureBase
{
public:
	MeasureAzimuth(void);
	~MeasureAzimuth(void);

	void clickEvent(osg::Vec3 pos);

	void moveEvent(osg::Vec3 pos);

	float calcResult();

	void endMeasure();
private:
	void init();

private:
	osg::ref_ptr<PlaceNode>	m_pNText;
	osg::ref_ptr<GeometryLine> m_pMainLine;
};
