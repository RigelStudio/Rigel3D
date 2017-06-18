#include "MeasureTool.h"

MeasureTool* MeasureTool::m_pSelf = NULL;

MeasureTool::MeasureTool(void)
{
	m_pHandler = NULL;
	m_pMeasureBase = NULL;
}

MeasureTool::~MeasureTool(void)
{
	if (m_pMeasureBase != NULL)
	{
		delete m_pMeasureBase;
	}
	if (m_pMeasureGroup != NULL)
	{
		m_pRoot->removeChild(m_pMeasureGroup);
	}
	if (m_pHandler != NULL)
	{
		m_pViewer->removeEventHandler(m_pHandler);
	}
	m_pHandler = NULL;
	m_pMeasureBase = NULL;
	m_pMeasureGroup = NULL;
}

MeasureTool* MeasureTool::ins()
{
	if (m_pSelf == NULL)
	{
		m_pSelf = new MeasureTool;
	}
	return m_pSelf;
}

void MeasureTool::destory()
{
	if (m_pSelf != NULL)
	{
		delete m_pSelf;
		m_pSelf = NULL;
	}
}

void MeasureTool::selectTool(MeasureType type)
{
	cancelTool();
	switch (type)
	{
	case Measure_Area:
		{
			m_pMeasureBase = new MeasureArea;
			m_currentType = Measure_Area;
			break;
		}
	case Measure_Length:
		{
			m_pMeasureBase = new MeasureLength;
			m_currentType = Measure_Length;
			break;
		}
	case Measure_Height:
		{
			m_pMeasureBase = new MeasureHeight;
			m_currentType = Measure_Height;
			break;
		}
	case Measure_Angle:
		{
			m_pMeasureBase = new MeasureAngle;
			m_currentType = Measure_Angle;
			break;
		}
	case Measure_Azimuth:
		{
			m_pMeasureBase = new MeasureAzimuth;
			m_currentType = Measure_Azimuth;
			break;
		}
	case Measure_PorArea:
		{
			m_pMeasureBase = new MeasureProjectionArea;
			m_currentType = Measure_PorArea;
			break;
		}
	case Measure_ProLength:
		{
			m_pMeasureBase = new MeasureProjectionLength;
			m_currentType = Measure_ProLength;
			break;
		}
	default: Measure_None;
			break;
	} 
	m_pMeasureBase->setMeasureGroup(m_pMeasureGroup);
	m_pMeasureBase->setImagePath(m_strImagePath);
	m_pHandler = new MeasureHandlerBase(m_pMeasureBase);
	m_pViewer->addEventHandler(m_pHandler);
}

void MeasureTool::cancelTool()
{
	if (m_pMeasureBase != NULL)
	{
		delete m_pMeasureBase;
		m_pMeasureBase = NULL;
	}
	m_currentType = Measure_None;
	m_pViewer->removeEventHandler(m_pHandler);
	m_pMeasureGroup->removeChildren(0, m_pMeasureGroup->getNumChildren());
}

void MeasureTool::init(osgViewer::Viewer* viewer, osg::Group* root)
{
	m_pRoot = root;
	m_pViewer = viewer;
	m_pMeasureGroup = new osg::Group;
	m_pRoot->addChild(m_pMeasureGroup);
	osg::StateSet* stateSet = m_pMeasureGroup->getOrCreateStateSet();
	stateSet->setMode(GL_LIGHTING, 4);
	stateSet->setMode(GL_BLEND, 5);
	stateSet->setMode(GL_DEPTH_TEST, 4);
	stateSet->setRenderBinDetails(10, "RenderBin");
}

void MeasureTool::setImagePath(std::string imagePath)
{
	m_strImagePath = imagePath;
}

