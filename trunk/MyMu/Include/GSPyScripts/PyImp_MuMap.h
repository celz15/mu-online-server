/*
 * PyImp_MuMap.h
 *
 *  Created on: 2009-06-24
 *      Author: Administrator
 */

#ifndef PYIMP_MUMAP_H_
#define PYIMP_MUMAP_H_
#include <Python.h>
#include "MuObiects/MuMap.h"

typedef struct
{
	PyObject_HEAD /* required py macro */
	MuMap * maps;
} MuPy_Map;

extern PyTypeObject Map_Type;

PyObject * createFromMuMap(MuMap * m);
PyObject * MuMap_Init( void );


#endif /* PYIMP_MUMAP_H_ */
