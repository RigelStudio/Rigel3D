/*************************************************
// Copyright(C) MEEngine Team
// File name:    InputLib.cpp
// Author:       ∑Î—«
// Version:      0.1.0
// Date:         2017-5-11
// Description:  “¿¿µø‚
// History:
*************************************************/
#ifndef OSGGRAPHICS_INPUTLIB_H
#define OSGGRAPHICS_INPUTLIB_H

#ifdef _DEBUG
//#pragma comment(lib,"OpenThreadsd.lib")
#pragma comment(lib,"osgd.lib")
#pragma comment(lib,"osgDBd.lib")
#pragma comment(lib,"osgGAd.lib")
#pragma comment(lib,"osgViewerd.lib")

#pragma comment(lib,"RigelQtd.lib")
#pragma comment(lib,"RigelCored.lib")

#else
#pragma comment(lib,"OpenThreads.lib")
#pragma comment(lib,"osg.lib")
#pragma comment(lib,"osgDB.lib")
#pragma comment(lib,"osgGA.lib")
#pragma comment(lib,"osgViewer.lib")

#pragma comment(lib,"RigelQt.lib")
#pragma comment(lib,"RigelCore.lib")

#endif

#endif // OSGGRAPHICS_INPUTLIB_H
