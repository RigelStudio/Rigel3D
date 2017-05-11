#pragma once

#include <QWidget>
#include "ui_BottomMenu.h"

class BottomMenu : public QWidget
{
	Q_OBJECT

public:
	BottomMenu(QWidget *parent = Q_NULLPTR);
	~BottomMenu();

private:
	Ui::BottomMenu ui;
};
