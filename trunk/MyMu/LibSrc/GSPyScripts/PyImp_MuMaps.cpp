/*
 * PyImp_MuMaps.c
 *
 *  Created on: 2009-06-24
 *      Author: Administrator
 */
#include "GSPyScripts/PyImp_MuMaps.h"
//#include "GSPyScripts/PyImp_MuMap.h"
#include <Python.h>
//#include "MuObiects/MuMaps.h"

//class methods
static PyObject *MuMaps_getMapC(MuPy_Maps * self);
static PyObject *MuMaps_getMap(MuPy_Maps * self, PyObject * args);
static PyObject *MuMaps_str(MuPy_Maps * self);
static int MuMaps_print(MuPy_Maps *obj, FILE *fp, int flags);

//object create/geted
static PyObject *M_Maps_GetInstance(PyObject * self);
static void Maps_DeAlloc(MuPy_Maps * self);
static PyObject *Maps_GetAttr(MuPy_Maps * self, char *name);
static int Maps_SetAttr(MuPy_Maps* self, char *name, PyObject * value);

static char M_Maps_doc[] = "";
static char M_Maps_GetInstance_doc[] = "() - return the mapsmng class";

//definitions pythons module
struct PyMethodDef M_Maps_methods[] =
{
{ "GetInstance", (PyCFunction) M_Maps_GetInstance, METH_NOARGS,
		M_Maps_GetInstance_doc },
//{ "getMap", (PyCFunction) MuMaps_getMap, METH_VARARGS, "() - get map by id" },
{ NULL, NULL, 0, NULL } };

//class methods list
static PyMethodDef MuPy_Maps_methods[] =
{
{ "getMapsCount", (PyCFunction) MuMaps_getMapC, METH_NOARGS,
		"() - Return Registers maps count" },

{ NULL, NULL, 0, NULL } };

//maph type definition


PyTypeObject Maps_Type
=
{	PyObject_HEAD_INIT(&PyType_Type)
	0,
	"MuServer.MapsMng",
	sizeof( MuPy_Maps ), /* tp_basicsize */
	0, /* tp_itemsize */
	/* methods */
	( destructor ) Maps_DeAlloc, /* tp_dealloc */
	( printfunc ) MuMaps_print, /* tp_print */
	( getattrfunc ) Maps_GetAttr, /* tp_getattr */
	( setattrfunc ) Maps_SetAttr, /* tp_setattr */
	0,//( cmpfunc ) World_Compare,	/* tp_compare */
	( reprfunc ) MuMaps_str,	/* tp_repr */
	0, /* tp_as_number */
	0, /* tp_as_sequence */
	0, /* tp_as_mapping */
	0, /* tp_as_hash */
	0, 0, 0, 0, 0, 0,
	0, /* tp_doc */
	0, 0, 0, 0, 0, 0,
	MuPy_Maps_methods, /* tp_methods */
	0, /* tp_members */
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

static void Maps_DeAlloc(MuPy_Maps * self)
{
	self->maps = NULL;
	PyObject_DEL(self);
}

static PyObject *M_Maps_GetInstance(PyObject * self)
{
	MuPy_Maps *m = NULL;

	m = (MuPy_Maps *) PyObject_NEW( MuPy_Maps, &Maps_Type );
	m->maps = MuMaps::getInstance();
	return (PyObject *) m;
}

PyObject* MuMaps_Init(void)
{
	PyObject *submodule;
	//Maps_Type.ob_type = &PyType_Type;
	submodule = Py_InitModule3( "MuServer.MapsMng",
			M_Maps_methods, M_Maps_doc );
	return (submodule);
}

static PyObject *Maps_GetAttr(MuPy_Maps * self, char *name)
{
	if (strcmp(name, "count") == 0)
		return MuMaps_getMapC(self);
	if (strcmp(name , "Maps")==0)
		return MuMaps_str(self);
	return Py_FindMethod(MuPy_Maps_methods, (PyObject *) self, name);
}

static int Maps_SetAttr(MuPy_Maps * self, char *name, PyObject * value)
{
	PyObject *error = NULL;
	PyObject *valtuple = Py_BuildValue("(O)", value);
	if (!valtuple)
		return 0;
	else
	{
		Py_DECREF( value )
;		Py_DECREF( valtuple );
		return 0;
	}
	Py_DECREF(valtuple);
	if( error != Py_None )
	return -1;
	Py_DECREF( Py_None );
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////
static PyObject *MuMaps_getMapC(MuPy_Maps * self)
{

	return PyInt_FromSize_t(self->maps->getNMap());
}

//static PyObject *MuMaps_getMap(MuPy_Maps * self, PyObject * args)
//{
//	int number = -1;
//	MuMap *m = NULL;
//	PyArg_Parse(args, "i", &number);
//	if (number != -1)
//		m = self->maps->getMap(number);
//	if (number != NULL)
//		return MuMap_CreatePyObject(m);
//	Py_RETURN_NONE;
//}
static PyObject *MuMaps_str(MuPy_Maps * self)
{
	if(self->maps==NULL)return PyString_FromFormat("Error Lost pointer to MapsMng");
	std::string ret;
	char t[20];
	ret.append("MapsMng Dump Known Maps\n");
	for (int i =0 ; i<self->maps->getNMap();i++)
	{
		sprintf(t,"--[%d]\t[%s]\n",i,self->maps->getMap(i)->getName().c_str());
		ret.append(t);
	}
	ret.append("MapsMng end of dump\n");
	return PyString_FromString(ret.c_str());
}

static int MuMaps_print(MuPy_Maps *self, FILE *fp, int flags)
{
	if(self->maps==NULL)return 0;
	std::string ret;
	char t[20];
	ret.append("MapsMng Dump Known Maps\n");
	for (int i =0 ; i<self->maps->getNMap();i++)
	{
		sprintf(t,"--[%d]\t[%s]\n",i,self->maps->getMap(i)->getName().c_str());
		ret.append(t);
	}
	ret.append("MapsMng end of dump\n");
		fprintf(fp,ret.c_str());
		return 0;
}
