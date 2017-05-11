/*  	
 *@file   Export.h
 *@brief  brief  description  
 *@author louyk
 *@date   2017/05/11
 *@version 0.1.0
 *@note  
 */
#ifndef MECORE_EXPORT_H
#define MECORE_EXPORT_H

#ifdef MECORE_EXPORTS
#	define MECORE_EXPORT __declspec(dllexport)
#else 
#	define MECORE_EXPORT __declspec(dllimport)
#endif 

#endif // MECORE_EXPORT_H
