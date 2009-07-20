/*
 * PyImp_MuMaps.h
 *
 *  Created on: 2009-06-24
 *      Author: Administrator
 */

#ifndef PYIMP_MUMAPS_H_
#define PYIMP_MUMAPS_H_
#include <Python.h>
#include "MuObiects/MuMaps.h"

typedef struct
{
	PyObject_HEAD /* required py macro */
	MuMaps * maps;
} MuPy_Maps;

extern PyTypeObject Maps_Type;
PyObject *MuMaps_Init( void );



#endif /* PYIMP_MUMAPS_H_ */
