#include "MeasureLength.h"

MeasureLength::MeasureLength(void)
{
	m_pMainLine = NULL;
}

MeasureLength::~MeasureLength(void)
{
	if (m_pMainLine != NULL)
	{
		delete m_pMainLine;
		m_pMainLine = NULL;
	}
}

void MeasureLength::clickEvent(osg::Vec3 pos)
{
	if (pos == osg::Vec3())
	{
		return;
	}

	if (m_pMainLine != NULL)
	{
		m_pMainLine->addPoint(pos);
		float length = calcResult();
		m_numVertexs = m_pMainLine->pointSize();
	}
}

void MeasureLength::moveEvent(osg::Vec3 pos)
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
		m_pMainLine->setPoint(m_numVertexs, pos);
	}
}

float MeasureLength::calcResult()
{
	if (m_pMainLine->pointSize() < 2)
	{
		return 0.0;
	}
	float length = 0.f;
	for (size_t i = 0; i < m_pMainLine->pointSize() - 1; i++)
	{
		length += (m_pMainLine->atPoint(i+1) - 
			m_pMainLine->atPoint(i)).length();
	}
	return length;
}



void MeasureLength::endMeasure()
{
	m_isStart = false;
	m_isEnd = true;
	if (m_pCloseButton != NULL)
	{
		m_pTipText->setText(L"双击开始测量");
		m_pCloseButton->setNodeMask(true);
	}
	m_pMainLine = NULL;
}

void MeasureLength::init()
{
	osg::Group* root = new osg::Group;
	m_isStart = true;
	m_numVertexs = 0;
	m_pMainLine = new GeometryLine;
	m_pMainLine->setColor(osg::Vec4(1, 1, 0, 0.5));
	m_pMainLine->setWidth(2.0);
	m_pGeomGeode = new osg::Geode;
	m_pGeomGeode->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, 4);
	m_pGeomGeode->addDrawable(m_pMainLine);
	root->addChild(m_pGeomGeode);

	m_pTextInfo = new PlaceNode;
	m_pTextInfo->setTextColor(osg::Vec4(0.8, 0, 0, 1));
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