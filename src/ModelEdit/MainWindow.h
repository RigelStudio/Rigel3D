/*************************************************
// Copyright(C) MEEngine Team
// File name:    MainWindow.h
// Author:       ·ëÑÇ
// Version:      1.0
// Date:         2017-5-11
// Description:  Ö÷´°¿Ú
//	History:
*************************************************/
#ifndef MODELEDIT_MAINWINDOW_H
#define MODELEDIT_MAINWINDOW_H
#include <QtWidgets/QMainWindow>
#include <QGraphicsProxyWidget>
#include "ui_MainWindow.h"
#include "MainWidget/AppHeadeTitle.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);

protected:
	virtual void resizeEvent(QResizeEvent* event);

private:
	void initScene();

	void initSimon();

	void initKestiny();
private:
	Ui::MainWindowClass ui;
	AppHeadeTitle* m_pAppTitle;
	QGraphicsProxyWidget* m_pTitleWidget;
};

#endif // MODELEDIT_MAINWINDOW_H
