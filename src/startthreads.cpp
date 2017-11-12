/*
 * StartThreads.cpp
 *
 *  Created on: 3 juni 2017
 *      Author: Otur1337
 */
#pragma once
#include "startthreads.h"

#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include <numeric>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <stdint.h> // <cstdint> requires c++11 support
#include <fstream>
#include <cstdlib>
#include <pthread.h>
#if __cplusplus > 199711L || _MSC_VER > 1800
#include <functional>
#endif

#ifdef WIN32
#include <Windows.h>
#else
#define Sleep(x) sleep(x/1000)
#endif
#include <Python.h>

#if PY_MAJOR_VERSION >= 3
#define PyString_FromString PyUnicode_FromString
#endif

bool res;

using namespace std;
PyObject *pModuledash, *pMain1, *pMain2, *pValue100, *pValue200,*pArgEmpty1,*pArgEmpty2;
    

Start::Start(void)
{
	Py_Initialize();
    PyEval_InitThreads();

 	PyObject *sys = PyImport_ImportModule("sys");
	PyObject *path = PyObject_GetAttrString(sys, "path");
	PyList_Append(path, PyString_FromString("."));
	
	PyObject *pFileNamedash = PyString_FromString("dashThread");   //Get the name of the module
	pModuledash = PyImport_Import(pFileNamedash);     //Get the module

	Py_DECREF(pFileNamedash);
}


void Start::Start_Python()
{
	
	cout << "running_start_python111111" << endl;

    if (pModuledash != NULL) {
		pMain1 = PyObject_GetAttrString(pModuledash,"start");

		if (pMain1 && PyCallable_Check(pMain1)) {
		}
		else {
			if (PyErr_Occurred())
				PyErr_Print();
				fprintf(stderr, "Cannot find function" );
		}
	}
	else {
		PyErr_Print();
		fprintf(stderr, "Failed to load ");
	}

    pValue100 = PyObject_CallObject(pMain1,pArgEmpty1);

	Py_DECREF(pMain1);   	
   	Py_DECREF(pValue100);

} 

Start::~Start()
{
	Py_Finalize();
}

