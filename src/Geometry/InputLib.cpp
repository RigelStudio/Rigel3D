/*************************************************
// Copyright(C) MEEngine Team
// File name:    InputLib.cpp
// Author:       ∑Î—«
// Version:      0.1.0
// Date:         2017-5-11
// Description:  “¿¿µø‚
// History:
*************************************************/
#ifndef GEOMETRYMODEL_LIB_H
#define GEOMETRYMODEL_LIB_H

#ifdef _DEBUG
#pragma comment(lib,"OpenThreadsd.lib")
#pragma comment(lib,"osgd.lib")
#pragma comment(lib,"osgDBd.lib")
#pragma comment(lib,"osgUtild.lib")

#pragma comment(lib,"MEMathd.lib")

#else
#pragma comment(lib,"OpenThreads.lib")
#pragma comment(lib,"osg.lib")
#pragma comment(lib,"osgDB.lib")
#pragma comment(lib,"osgUtil.lib")

#pragma comment(lib,"MEMath.lib")
#endif

#endif // GEOMETRYMODEL_LIB_H
