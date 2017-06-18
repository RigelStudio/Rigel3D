#ifndef MEASUREBASE_H
#define MEASUREBASE_H
#include "Export.h"
#include <osg/Array>
#include <osg/Group>
#include <osg/Geode>

const std::string CLOSEBUTTON = "CloseButton";

class MEPLOTTING_EXPORT MeasureBase : public osg::Group
{
public:
	MeasureBase(void);

	virtual ~MeasureBase(void);

	virtual void clickEvent(osg::Vec3 pos){}
	
	virtual void moveEvent(osg::Vec3 pos){}

	virtual float calcResult(){return 0;}

	virtual void startMeasure();

	virtual void endMeasure();
	
	void clearTheMeasure(osg::Node* node);

	bool isStart(){return m_isStart;}

	bool isEnd(){return m_isEnd;}

	void setImagePath(std::string &imagePath);
protected:
	virtual void init(){};
protected:
	size_t m_numVertexs;
	bool m_isStart;
	bool m_isEnd;
	std::string m_strImagePath;
	osg::ref_ptr<osg::Geode>		m_pGeomGeode;
};

#endif//MEASUREBASE_H