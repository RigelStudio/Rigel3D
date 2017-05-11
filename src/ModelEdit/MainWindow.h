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
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);

private:
	Ui::MainWindowClass ui;
};

#endif // MODELEDIT_MAINWINDOW_H
