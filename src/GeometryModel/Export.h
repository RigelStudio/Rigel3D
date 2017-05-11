#ifndef GEOMETRYMODEL_EXPORT_H
#define GEOMETRYMODEL_EXPORT_H

#if defined (GEOMETRYMODEL_EXPORTS)
#	define GEOMETRYMODEL_EXPORT __declspec(dllexport)
#else 
#	define GEOMETRYMODEL_EXPORT __declspec(dllimport)
#endif 

#endif