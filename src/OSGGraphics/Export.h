/*  	
 *@file   Export.h
 *@brief  brief  description  
 *@author louyk
 *@date   2017/05/11
 *@version 0.1.0
 *@note  
 */
#ifndef OSGGRAPHICS_EXPORT_H
#define OSGGRAPHICS_EXPORT_H

#if defined (OSGGRAPHICS_EXPORTS)
#	define OSGWIDGET_EXPORT __declspec(dllexport)
#else 
#	define OSGWIDGET_EXPORT __declspec(dllimport)
#endif 

#endif // OSGGRAPHICS_EXPORT_H
