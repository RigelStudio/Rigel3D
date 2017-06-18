#include <MeasureTool/MeasureAngle.h>

MeasureAngle::MeasureAngle(void)
{
	m_pMainLine = NULL;
}

MeasureAngle::~MeasureAngle(void)
{
	if (m_pMainLine != NULL)
	{
		delete m_pMainLine;
		m_pMainLine = NULL;
	}
}

void MeasureAngle::clickEvent(osg::Vec3 pos)
{
	if (pos == osg::Vec3())
	{
		return;
	}

	if (m_pMainLine != NULL)
	{
		if (m_pMainLine->pointSize() < 3)
		{
			m_pMainLine->addPoint(pos);
			m_pGeodeMark->addMarkSphere(pos);
		}
	}
}

void MeasureAngle::moveEvent(osg::Vec3 pos)
{
	if (pos == osg::Vec3())
	{
		return;
	}
	if (m_pTipText != NULL)
	{
		if (m_isStart)
		{
			m_pTipText->setText(L"Ë«»÷½áÊø²âÁ¿");
		}
		else
		{
			m_pTipText->setText(L"Ë«»÷¿ªÊ¼²âÁ¿");
		}
		m_pTipText->setPosition(pos);
	}

	if (m_pMainLine != NULL)
	{
		if (m_pMainLine->pointSize() == 1)
		{
			m_pMainLine->addPoint(pos);
			osg::Vec3 thePos = m_pMainLine->atPoint(0);
			thePos.z() = pos.z();
			m_pMainLine->addPoint(thePos);
			m_pMainLine->addPoint(m_pMainLine->atPoint(0));
		}
		if (m_pMainLine->pointSize() == 4)
		{
			osg::Vec3 thePos = m_pMainLine->atPoint(0);
			thePos.z() = pos.z();
			m_pMainLine->setPoint(1, pos);
			m_pMainLine->setPoint(2, thePos);
			float length = calcResult();
			std::wstring string = std::wstring(L"¸©Ñö½Ç: ")+ 
				Conv::double2wstr(length) +  std::wstring(L"¡ã");
			m_pTextInfo->setText(string);
			m_pTextInfo->setPosition(thePos);
		}
	}
}

float MeasureAngle::calcResult()
{
	float angle = 0.0;
	osg::Vec3 vectorA = m_pMainLine->atPoint(1) - m_pMainLine->atPoint(0);
	osg::Vec3 vectorB = m_pMainLine->atPoint(2) - m_pMainLine->atPoint(0);
	angle = STMath::getAngleByVector(vectorA, vectorB);
	angle = abs(90.-angle);
	return angle;
}

void MeasureAngle::endMeasure()
{
	m_isStart = false;
	m_isEnd = true;
	if (m_pCloseButton != NULL)
	{
		m_pTipText->setText(L"Ë«»÷¿ªÊ¼²âÁ¿");
		m_pCloseButton->setNodeMask(true);
		m_pCloseButton->setPosition(m_pMainLine->lastPoint());
	}
	m_pMainLine = NULL;
}

void MeasureAngle::init()
{
	osg::Group* root = new osg::Group;
	m_isStart = true;
	m_isEnd = false;

	m_pMainLine = new GeometryLine;
	m_pMainLine->setColor(osg::Vec4(1.0, 1, 0, 0.5));
	m_pMainLine->setWidth(2.0);
	m_pGeomGeode = new osg::Geode;
	m_pGeomGeode->addDrawable(m_pMainLine);
	root->addChild(m_pGeomGeode);

	m_pTextInfo = new PlaceNode;
	m_pTextInfo->setTextColor(osg::Vec4(1.0, 0, 0, 1));
	m_pTextInfo->setFontSize(15);
	m_pTextInfo->setTextPosition(osg::Vec3(0, -15,0));
	m_pTextInfo->setBackMode(LabelBase::FILL_BOX);
	m_pTextInfo->setBackColor(osg::Vec4(1, 1, 1, 0.5));
	root->addChild(m_pTextInfo);

	m_pCloseButton = new PlaceNode;
	m_pCloseButton->setImage(m_strImagePath);
	m_pCloseButton->setTextColor(osg::Vec4(1, 1, 1, 1));
	m_pCloseButton->setName(CLOSEBUTTON);
	m_pCloseButton->setFontSize(15);
	m_pCloseButton->setNodeMask(0x0);
	root->addChild(m_pCloseButton);

	m_pGeodeMark = new MeasureMarkSphere;
	root->addChild(m_pGeodeMark);

	m_pMeasGroup->addChild(root);
}
