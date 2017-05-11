#ifndef MODELEDIT_LIB_H
#define MODELEDIT_LIB_H

#ifdef _DEBUG
#pragma comment(lib,"OpenThreadsd.lib")
#pragma comment(lib,"osgd.lib")
#pragma comment(lib,"osgGAd.lib")
#pragma comment(lib,"osgViewerd.lib")

#else
#pragma comment(lib,"OpenThreads.lib")
#pragma comment(lib,"osg.lib")
#pragma comment(lib,"osgGA.lib")
#pragma comment(lib,"osgDB.lib")
#pragma comment(lib,"osgText.lib")
#pragma comment(lib,"osgUtil.lib")
#pragma comment(lib,"osgViewer.lib")

#pragma comment(lib,"GUITool.lib")
#pragma comment(lib,"osgGraphics.lib")

#endif

#endif//MODELEDIT_LIB_H