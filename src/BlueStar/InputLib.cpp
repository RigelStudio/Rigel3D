#ifndef BLUESTAR_INPUTLIB_H
#define BLUESTAR_INPUTLIB_H

#ifdef _DEBUG
#pragma comment(lib,"OpenThreadsd.lib")
#pragma comment(lib,"osgd.lib")
#pragma comment(lib,"osgGAd.lib")
#pragma comment(lib,"osgDBd.lib")
#pragma comment(lib,"osgTextd.lib")
#pragma comment(lib,"osgUtild.lib")
#pragma comment(lib,"osgViewerd.lib")
#pragma comment(lib,"MECored.lib")

#else
#pragma comment(lib,"OpenThreads.lib")
#pragma comment(lib,"osg.lib")
#pragma comment(lib,"osgGA.lib")
#pragma comment(lib,"osgDB.lib")
#pragma comment(lib,"osgText.lib")
#pragma comment(lib,"osgUtil.lib")
#pragma comment(lib,"osgViewer.lib")

#pragma comment(lib,"MECore.lib")

#endif

#endif // MODELEDIT_INPUTLIB_H
