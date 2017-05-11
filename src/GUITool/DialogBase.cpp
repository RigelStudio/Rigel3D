#include "DialogBase.h"
#include <QSpacerItem>
#include <QApplication>


DialogBase::DialogBase(QWidget *parent)
	: QDialog(parent)
{
	setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
	setAttribute(Qt::WA_TranslucentBackground);
	setWindowOpacity(0.9);
	setMouseTracking(true);

	m_dir = NONE;
	m_isMove = false;
	m_isMoveAble = true;
	m_isResizeAble = false;
	m_dragPoint = QPoint(0, 0);
	
	m_pTitleWid = new QWidget(this);
	initTitle();
}

DialogBase::~DialogBase()
{

}

void DialogBase::mousePressEvent(QMouseEvent* e)
{
	if (e->button() ==  Qt::LeftButton)
	{
		m_isMove = true;
		m_dragPoint = e->globalPos() - this->pos();

		//可变大小
		m_isResizeAble = true;
		if (m_dir != NONE) {
			this->mouseGrabber();
		}
		else {
			m_dragPosition = e->globalPos() - this->frameGeometry().topLeft();
		}
	}
	else
	{
		QDialog::mousePressEvent(e);
	}
}

void DialogBase::mouseMoveEvent(QMouseEvent* e)
{
	if (m_isMove && m_dir == NONE && m_isMoveAble)
	{
		move(e->globalPos() - m_dragPoint);
	}

	//可变大小
	QPoint gloPoint = e->globalPos();
	QRect rect = this->rect();
	QPoint tl = mapToGlobal(rect.topLeft());
	QPoint rb = mapToGlobal(rect.bottomRight());

	if (!m_isResizeAble) {
		this->region(gloPoint);
	}
	else {

		if (m_dir != NONE) {
			QRect rMove(tl, rb);

			switch (m_dir) {
			case LEFT:
				if (rb.x() - gloPoint.x() <= this->minimumWidth())
					rMove.setX(tl.x());
				else
					rMove.setX(gloPoint.x());
				break;
			case RIGHT:
				rMove.setWidth(gloPoint.x() - tl.x());
				break;
			case UP:
				if (rb.y() - gloPoint.y() <= this->minimumHeight())
					rMove.setY(tl.y());
				else
					rMove.setY(gloPoint.y());
				break;
			case DOWN:
				rMove.setHeight(gloPoint.y() - tl.y());
				break;
			case LEFTTOP:
				if (rb.x() - gloPoint.x() <= this->minimumWidth())
					rMove.setX(tl.x());
				else
					rMove.setX(gloPoint.x());
				if (rb.y() - gloPoint.y() <= this->minimumHeight())
					rMove.setY(tl.y());
				else
					rMove.setY(gloPoint.y());
				break;
			case RIGHTTOP:
				rMove.setWidth(gloPoint.x() - tl.x());
				rMove.setY(gloPoint.y());
				break;
			case LEFTBOTTOM:
				rMove.setX(gloPoint.x());
				rMove.setHeight(gloPoint.y() - tl.y());
				break;
			case RIGHTBOTTOM:
				rMove.setWidth(gloPoint.x() - tl.x());
				rMove.setHeight(gloPoint.y() - tl.y());
				break;
			default:
				break;
			}
			this->setGeometry(rMove);
		}
		else {
			if (m_isMoveAble)
			{
				move(e->globalPos() - m_dragPosition);
			}	
			e->accept();
		}
	}
	QDialog::mouseMoveEvent(e);
}

void DialogBase::mouseReleaseEvent(QMouseEvent* e)
{
	m_isMove = false;

	//可变大小
	if (e->button() == Qt::LeftButton) {
		m_isResizeAble = false;
		if (m_dir != NONE) {
			this->releaseMouse();
			this->setCursor(QCursor(Qt::ArrowCursor));
		}
	}

	QDialog::mouseReleaseEvent(e);
}

void DialogBase::region(const QPoint &cursorGlobalPoint)
{
	// 获取窗体在屏幕上的位置区域，tl为topleft点，rb为rightbottom点
	QRect rect = this->rect();
	QPoint tl = mapToGlobal(rect.topLeft());
	QPoint rb = mapToGlobal(rect.bottomRight());

	int x = cursorGlobalPoint.x();
	int y = cursorGlobalPoint.y();

	if (tl.x() + PADDING >= x && tl.x() <= x && tl.y() + PADDING >= y && tl.y() <= y) {
		// 左上角
		m_dir = LEFTTOP;
		QApplication::setOverrideCursor(Qt::SizeFDiagCursor);
		//this->setCursor(QCursor(Qt::SizeFDiagCursor));  // 设置鼠标形状
	}
	else if (x >= rb.x() - PADDING && x <= rb.x() && y >= rb.y() - PADDING && y <= rb.y()) {
		// 右下角
		m_dir = RIGHTBOTTOM;
		QApplication::setOverrideCursor(Qt::SizeFDiagCursor);
		//this->setCursor(QCursor(Qt::SizeFDiagCursor));
	}
	else if (x <= tl.x() + PADDING && x >= tl.x() && y >= rb.y() - PADDING && y <= rb.y()) {
		//左下角
		m_dir = LEFTBOTTOM;
		QApplication::setOverrideCursor(Qt::SizeBDiagCursor);
		//this->setCursor(QCursor(Qt::SizeBDiagCursor));
	}
	else if (x <= rb.x() && x >= rb.x() - PADDING && y >= tl.y() && y <= tl.y() + PADDING) {
		// 右上角
		m_dir = RIGHTTOP;
		QApplication::setOverrideCursor(Qt::SizeBDiagCursor);
		//this->setCursor(QCursor(Qt::SizeBDiagCursor));
	}
	else if (x <= tl.x() + PADDING && x >= tl.x()) {
		// 左边
		m_dir = LEFT;
		QApplication::setOverrideCursor(Qt::SizeHorCursor);
		//this->setCursor(QCursor(Qt::SizeHorCursor));
	}
	else if (x <= rb.x() && x >= rb.x() - PADDING) {
		// 右边
		m_dir = RIGHT;
		QApplication::setOverrideCursor(Qt::SizeHorCursor);
		//this->setCursor(QCursor(Qt::SizeHorCursor));
	}
	else if (y >= tl.y() && y <= tl.y() + PADDING){
		// 上边
		m_dir = UP;
		QApplication::setOverrideCursor(Qt::SizeVerCursor);
		//this->setCursor(QCursor(Qt::SizeVerCursor));
	}
	else if (y <= rb.y() && y >= rb.y() - PADDING) {
		// 下边
		m_dir = DOWN;
		QApplication::setOverrideCursor(Qt::SizeVerCursor);
		//this->setCursor(QCursor(Qt::SizeVerCursor));
	}
	else {
		// 默认
		m_dir = NONE;
		QApplication::setOverrideCursor(Qt::ArrowCursor);
		//this->setCursor(QCursor(Qt::ArrowCursor));
	}
}

void DialogBase::setMoveEanable(bool isMove /*= true*/)
{
	m_isMoveAble = isMove;
}

void DialogBase::leaveEvent(QEvent *)
{
	m_dir = NONE;
	QApplication::setOverrideCursor(Qt::ArrowCursor);
}

void DialogBase::initTitle()
{


	QString strStyle = QString("background-color: rgb(22,20,30);"
								"border-bottom:1px;border-style:solid;border-color:rgb(30,30,40);"
								""
								);
	m_pTitleWid->setStyleSheet(strStyle);
	QLayout* layout = this->layout();
	if (layout != NULL)
	{
		layout->addWidget(m_pTitleWid);
	}
}
