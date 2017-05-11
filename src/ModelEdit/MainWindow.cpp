#include "MainWindow.h"
#include "Core.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setCentralWidget(Core::ins()->getOSGView());
}
