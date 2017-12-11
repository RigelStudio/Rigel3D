/*  	
 *@file   Export.h
 *@brief  brief  description  
 *@author louyk
 *@date   2017/05/11
 *@version 0.1.0
 *@note  
 */
#ifndef RIGELCORE_EXPORT_H
#define RIGELCORE_EXPORT_H

#ifdef RIGELCORE
#	define DLL_EXPORT __declspec(dllexport)
#else 
#	define DLL_EXPORT __declspec(dllimport)
#endif 

#endif // MECORE_EXPORT_H
