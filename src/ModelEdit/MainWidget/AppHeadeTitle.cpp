#include "AppHeadeTitle.h"

AppHeadeTitle::AppHeadeTitle(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_TranslucentBackground);
	m_pCurrentButton = 0;

	connect(ui.pushButtonExit, SIGNAL(clicked()), this, SLOT(slotExit()));
	connect(ui.pushButtonDocMan, SIGNAL(clicked()), this, SLOT(slotClicked()));
	connect(ui.pushButtonDecisiondMan, SIGNAL(clicked()), this, SLOT(slotClicked()));
	connect(ui.pushButtonFightLayout, SIGNAL(clicked()), this, SLOT(slotClicked()));
	connect(ui.pushButtonDatabaseCenter, SIGNAL(clicked()), this, SLOT(slotClicked()));
	connect(ui.pushButtonAccidentCase, SIGNAL(clicked()), this, SLOT(slotClicked()));
}

AppHeadeTitle::~AppHeadeTitle()
{
}

void AppHeadeTitle::setOpenDocument(int state)
{
	switch (state)
	{
	case 0:
		// 文档管理
		m_pCurrentButton = ui.pushButtonDocMan;
		ui.pushButtonDocMan->setChecked(true);
		ui.pushButtonDecisiondMan->setChecked(false);
		break;
	case 1:
		// 流程化决策
		m_pCurrentButton = ui.pushButtonDecisiondMan;
		ui.pushButtonDocMan->setChecked(false);
		ui.pushButtonDecisiondMan->setChecked(true);
		break;
	default:
		break;
	}
	emit signalSelectChanged(m_pCurrentButton->objectName());
}

void AppHeadeTitle::slotClicked()
{
	QPushButton* pButton = dynamic_cast<QPushButton*>(sender());
	if (pButton)
	{
		ui.pushButtonDocMan->setChecked(false);
		ui.pushButtonDecisiondMan->setChecked(false);
		ui.pushButtonFightLayout->setChecked(false);
		ui.pushButtonDatabaseCenter->setChecked(false);
		ui.pushButtonAccidentCase->setChecked(false);

		pButton->setChecked(true);
		if (m_pCurrentButton != pButton)
		{
			m_pCurrentButton = pButton;
			emit signalSelectChanged(m_pCurrentButton->objectName());
		}
	}
}

void AppHeadeTitle::slotExit()
{
	emit signalExit();
}
