/*************************************************
 // Copyright(C)  MEEngine Team
 // File name:    Export
 // Author:       Simon       
 // Version:      1.0     
 // Date:         2017/05/12
 // Description:  数学函数导出
 //	History:
 *************************************************/
#ifndef MECORE_EXPORT_H
#define MECORE_EXPORT_H

#ifdef MEMATH_EXPORTS
#	define MECORE_EXPORT __declspec(dllexport)
#else 
#	define MECORE_EXPORT __declspec(dllimport)
#endif 

#endif // MECORE_EXPORT_H
