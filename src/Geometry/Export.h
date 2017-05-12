/*************************************************
// Copyright(C)
// File name:    Export
// Author:       冯亚
// Version:      1.0
// Date:         2017/05/11
// Description:  dll导出宏定义
//	History:
*************************************************/
#ifndef GEOMETRY_EXPORT_H
#define GEOMETRY_EXPORT_H

#if defined (GEOMETRY_EXPORTS)
#	define GEOMETRY_EXPORT __declspec(dllexport)
#else 
#	define GEOMETRY_EXPORT __declspec(dllimport)
#endif 

#endif // GEOMETRYMODEL_EXPORT_H
