#ifndef GUITOOL_EXPORT_H
#define GUITOOL_EXPORT_H

#if defined (GUITOOL_EXPORTS)
#	define GUITOOL_EXPORT __declspec(dllexport)
#else 
#	define GUITOOL_EXPORT __declspec(dllimport)
#endif 


#endif