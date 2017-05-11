/*************************************************
// Copyright(C) MEEngine Team
// File name:    Version.h
// Author:       kestiny
// Version:      1o.0
// Date:         2015-5-11
// Description:  引擎版本管理
//	History:
*************************************************/
#ifndef OSGGRAPHICS_VERSION_H
#define OSGGRAPHICS_VERSION_H
#include <string>
#include <stdio.h>
#include "Export.h"

#define MEENGINE_MAJOR_VERSION    0
#define MEENGINE_MINOR_VERSION    1
#define MEENGINE_PATCH_VERSION    0

class MECORE_EXPORT VersionApp
{
public:
	static const std::string getMEEngineVersion()
	{
		static char version[32];
		static int versionInit = 1;
		if (versionInit)
		{
			sprintf_s(version, "%d.%d.%d", MEENGINE_MAJOR_VERSION, MEENGINE_MINOR_VERSION, MEENGINE_PATCH_VERSION);

			versionInit = 0;
		}

		return version;
	}
};

#endif // OSGGRAPHICS_VERSION_H
