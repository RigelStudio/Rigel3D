#ifndef OSGGRAPHICS_LIB_H
#define OSGGRAPHICS_LIB_H

#ifdef _DEBUG
#pragma comment(lib,"OpenThreadsd.lib")
#pragma comment(lib,"osgd.lib")
#pragma comment(lib,"osgGAd.lib")
#pragma comment(lib,"osgViewerd.lib")

#else
#pragma comment(lib,"OpenThreads.lib")
#pragma comment(lib,"osg.lib")
#pragma comment(lib,"osgGA.lib")
#pragma comment(lib,"osgViewer.lib")

#endif

#endif//OSGGRAPHICS_LIB_H