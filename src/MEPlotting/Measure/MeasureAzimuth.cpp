#include <MeasureTool\MeasureAzimuth.h>

MeasureAzimuth::MeasureAzimuth(void)
{
	m_pMainLine = NULL;
	m_pNText = NULL;
}

MeasureAzimuth::~MeasureAzimuth(void)
{
	if (m_pMainLine != NULL)
	{
		delete m_pMainLine;
		m_pMainLine = NULL;
	}
	if(m_pNText != NULL)
	{
		delete m_pNText;
		m_pNText = NULL;
	}
}

void MeasureAzimuth::clickEvent(osg::Vec3 pos)
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
			m_pMainLine->addPoint(pos);
			m_pMainLine->addPoint(pos);
			m_pGeodeMark->addMarkSphere(pos);
		}
	}
}

void MeasureAzimuth::moveEvent(osg::Vec3 pos)
{
	if (pos == osg::Vec3())
	{
		return;
	}
	if (m_pTipText != NULL)
	{
		if (m_isStart)
		{
			m_pTipText->setText(L"双击结束测量");
		}
		else
		{
			m_pTipText->setText(L"双击开始测量");
		}
		m_pTipText->setPosition(pos);
	}

	if (m_pMainLine != NULL)
	{
		if (m_pMainLine->pointSize() == 3)
		{
			float _length = (m_pMainLine->atPoint(1) - pos).length();
			osg::Vec3 thePos = m_pMainLine->atPoint(1);
			thePos.y() += abs(_length);
			std::cout<<abs(_length)<<std::endl;
			m_pMainLine->setPoint(0, thePos);
			m_pMainLine->setPoint(2, pos);
			float length = calcResult();
			std::wstring string = std::wstring(L"方位角: ")+ 
				Conv::double2wstr(length) +  std::wstring(L"°");
			m_pTextInfo->setText(string);
			m_pTextInfo->setPosition(m_pMainLine->atPoint(2));

			m_pNText->setPosition(m_pMainLine->atPoint(0));
		}
	}
}

float MeasureAzimuth::calcResult()
{
	float angle = 0.0;
	osg::Vec3 vectorA = m_pMainLine->atPoint(0) - m_pMainLine->atPoint(1);
	osg::Vec3 vectorB = m_pMainLine->atPoint(2) - m_pMainLine->atPoint(1);
	angle = STMath::getAngleByVector(vectorA, vectorB);
	return angle;
}

void MeasureAzimuth::endMeasure()
{
	m_isStart = false;
	m_isEnd = true;
	if (m_pCloseButton != NULL)
	{
		m_pTipText->setText(L"双击开始测量");
		m_pCloseButton->setNodeMask(true);
		m_pCloseButton->setPosition(m_pMainLine->atPoint(2));
	}
	m_pMainLine = NULL;
}

void MeasureAzimuth::init()
{
	osg::Group* root = new osg::Group;
	m_isStart = true;
	m_isEnd = false;

	m_pMainLine = new GeometryLine;
	m_pMainLine->setColor(osg::Vec4(1, 1, 0, 0.5));
	m_pMainLine->setWidth(2.0);
	m_pMainLine->setPrimitiveSet(0, new osg::DrawArrays(
		osg::PrimitiveSet::LINES, 0, m_pMainLine->pointSize()));
	m_pGeomGeode = new osg::Geode;
	m_pGeomGeode->addDrawable(m_pMainLine);
	root->addChild(m_pGeomGeode);

	m_pTextInfo = new PlaceNode;
	m_pTextInfo->setTextColor(osg::Vec4(0.8, 0, 0, 1));
	m_pTextInfo->setFontSize(15);
	m_pTextInfo->setTextPosition(osg::Vec3(0, -15,0));
	m_pTextInfo->setBackMode(LabelBase::FILL_BOX);
	m_pTextInfo->setBackColor(osg::Vec4(1, 1, 1, 0.5));
	root->addChild(m_pTextInfo);
		
	m_pNText = new PlaceNode;
	m_pNText->setText("North");
	m_pNText->setTextColor(osg::Vec4(0.8, 0, 0, 1));
	m_pNText->setFontSize(20);
	m_pNText->setTextPosition(osg::Vec3(0, 5,0));
	m_pNText->setBackMode(LabelBase::FILL_BOX);
	m_pNText->setBackColor(osg::Vec4(1, 1, 1, 0.5));
	root->addChild(m_pNText);

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
