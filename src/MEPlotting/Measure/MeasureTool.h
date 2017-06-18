#ifndef MEASURETOOL_H
#define MEASURETOOL_H
#include "Export.h"
#include <MeasureTool/MeasureArea.h>
#include <MeasureTool/MeasureAngle.h>
#include <MeasureTool/MeasureLength.h>
#include <MeasureTool/MeasureHeight.h>
#include <MeasureTool/MeasureHandlerBase.h>
#include <MeasureTool/MeasureAzimuth.h>
#include <MeasureTool/MeasureProjectionArea.h>
#include <MeasureTool/MeasureProjectionLength.h>

class MEASURE_EXPORT MeasureTool
{
public:
	enum MeasureType
	{
		Measure_None,
		Measure_Area,
		Measure_Angle,
		Measure_Length,
		Measure_Height,
		Measure_Azimuth,
		Measure_PorArea,
		Measure_ProLength
	};

	static MeasureTool* ins();

	static void destory();

	void selectTool(MeasureType type);

	void cancelTool();

	MeasureType getCurrentType(){ return m_currentType; }

	void init(osgViewer::Viewer* viewer, osg::Group* root);

	void setImagePath(std::string imagePath);

private:
	MeasureTool(void);
	~MeasureTool(void);
	static MeasureTool* m_pSelf;
	MeasureType m_currentType;
	MeasureBase* m_pMeasureBase;
	std::string m_strImagePath;
	osg::ref_ptr<osg::Group> m_pRoot;
	osg::ref_ptr<osgViewer::Viewer> m_pViewer;
	osg::ref_ptr<osg::Group> m_pMeasureGroup;
	osg::ref_ptr<MeasureHandlerBase> m_pHandler;
};

#endif//MEASURETOOL_H