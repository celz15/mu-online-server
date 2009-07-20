/*
 * PyImp_MuMap.cpp
 *
 *  Created on: 2009-06-24
 *      Author: Administrator
 */
#include <Python.h>
#include "GSPyScripts/PyImp_MuMap.h"

//#include "GSPyScripts/PyImp_MuMap.h"
#include <Python.h>
//#include "MuObiects/MuMaps.h"

//class methods

//object create/geted
static char M_Map_doc[] = "Map class ";
static char M_Map_GetInstance_doc[] = "() - return the mapsmng class";

//definitions pythons module
struct PyMethodDef M_Map_methods[] =
{
//{ "GetInstance", (PyCFunction) M_Maps_GetInstance, METH_NOARGS,		M_Maps_GetInstance_doc },
//{ "getMap", (PyCFunction) MuMaps_getMap, METH_VARARGS, "() - get map by id" },
{ NULL, NULL, 0, NULL } };

//class methods list
static PyMethodDef MuPy_Map_methods[] =
{
//{ "getMapsCount", (PyCFunction) MuMaps_getMapC, METH_NOARGS,"() - Return Registers maps count" },

{ NULL, NULL, 0, NULL } };

//maph type definition


PyTypeObject Map_Type
=
{	PyObject_HEAD_INIT(&PyType_Type)
	0,
	"MuMap",
	sizeof( MuPy_Map ), /* tp_basicsize */
	0, /* tp_itemsize */
	/* methods */
	0,//( destructor ) Maps_DeAlloc, /* tp_dealloc */
	0,//( printfunc ) MuMaps_print, /* tp_print */
	0,//( getattrfunc ) Maps_GetAttr, /* tp_getattr */
	0,//( setattrfunc ) Maps_SetAttr, /* tp_setattr */
	0,//( cmpfunc ) World_Compare,	/* tp_compare */
	0,//( reprfunc ) MuMaps_str,	/* tp_repr */
	0, /* tp_as_number */
	0, /* tp_as_sequence */
	0, /* tp_as_mapping */
	0, /* tp_as_hash */
	0, 0, 0, 0, 0, 0,
	0, /* tp_doc */
	0, 0, 0, 0, 0, 0,
	MuPy_Map_methods, /* tp_methods */
	0, /* tp_members */
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};




PyObject * createFromMuMap(MuMap * m)
{
	MuPy_Map * temp=NULL;
	temp = (MuPy_Map *) PyObject_NEW(MuPy_Map , &Map_Type);
	temp->maps=m;
	return (PyObject *)temp;
}

PyObject* MuMap_Init(void)
{
	PyObject *submodule;
	submodule = Py_InitModule3( "MuMap",
			M_Map_methods, M_Map_doc );
	return (submodule);
}
