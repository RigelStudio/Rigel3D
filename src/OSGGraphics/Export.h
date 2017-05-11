#ifndef OSGWIDGET_EXPORT_H
#define OSGWIDGET_EXPORT_H

#if defined (OSGGRAPHICS_EXPORTS)
#	define OSGWIDGET_EXPORT __declspec(dllexport)
#else 
#	define OSGWIDGET_EXPORT __declspec(dllimport)
#endif 


#endif