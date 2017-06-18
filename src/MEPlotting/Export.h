/*************************************************
// Copyright(C)
// File name:    Export
// Author:       冯亚
// Version:      1.0
// Date:         2017/05/11
// Description:  dll导出宏定义
//	History:
*************************************************/
#ifndef MEPLOTTING_EXPORT_H
#define MEPLOTTING_EXPORT_H

#if defined (MEPLOTTING_EXPORTS)
#	define MEPLOTTING_EXPORT __declspec(dllexport)
#else 
#	define MEPLOTTING_EXPORT __declspec(dllimport)
#endif 

#endif // GEOMETRYMODEL_EXPORT_H
