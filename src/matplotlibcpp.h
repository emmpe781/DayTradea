#pragma once
#include <stdlib.h>
#include <vector>
#include <map>
#include <numeric>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <stdint.h> // <cstdint> requires c++11 support

#if __cplusplus > 199711L || _MSC_VER > 1800
#include <functional>
#endif

#include <Python.h>

#if PY_MAJOR_VERSION >= 3
#define PyString_FromString PyUnicode_FromString
#endif


namespace matplotlibcpp {


int runPython(std::vector<string> xvec,std::vector<double> yvec1,std::vector<double> yvec2) {
	PyObject *pName, *pModule, *pFunc;
	PyObject *pArgTuple1, *pArgTuple2,*pArgTuple3, *pValue, *pXVec, *pYVec1, *pYVec2;

	int i;

  	Py_Initialize();
	PyObject *sys = PyImport_ImportModule("sys");
	PyObject *path = PyObject_GetAttrString(sys, "path");
	PyList_Append(path, PyString_FromString("."));
	
	pName = PyString_FromString("pythonToEmbed");   //Get the name of the module
	pModule = PyImport_Import(pName);     //Get the module
	Py_DECREF(pName);
	
	if (pModule != NULL) {
		pFunc = PyObject_GetAttrString(pModule, "plotStdVectors");   //Get the function by its name
		/* pFunc is a new reference */
		
		if (pFunc && PyCallable_Check(pFunc)) {
			//Set up a tuple that will contain the function arguments. In this case, the
			//function requires two tuples, so we set up a tuple of size 2.
			pArgTuple1 = PyTuple_New(2);
			pArgTuple2 = PyTuple_New(2);
			pArgTuple3 = PyTuple_New(2);

			//Transfer the C++ vector to a python tuple
			pXVec = PyTuple_New(xvec.size());	
			for (i = 0; i < xvec.size(); ++i) {
				pValue = PyString_FromString(xvec[i].c_str());
				if (!pValue) {
					Py_DECREF(pXVec);
					Py_DECREF(pModule);
					fprintf(stderr, "Cannot convert array value");
					return 1;
				}
				PyTuple_SetItem(pXVec, i, pValue);
			}

			//Transfer the other C++ vector to a python tuple
			pYVec1 = PyTuple_New(yvec1.size());	
			for (i = 0; i < yvec1.size(); ++i) {
				pValue = PyFloat_FromDouble(yvec1[i]);
				if (!pValue) {
					Py_DECREF(pYVec1);
					Py_DECREF(pModule);
					fprintf(stderr, "Cannot convert array value");
					return 1;
				}
				PyTuple_SetItem(pYVec1, i, pValue); //
			}

		//Transfer the other C++ vector to a python tuple
			pYVec2 = PyTuple_New(yvec2.size());	
			for (i = 0; i < yvec2.size(); ++i) {
				pValue = PyFloat_FromDouble(yvec2[i]);
				if (!pValue) {
					Py_DECREF(pYVec2);
					Py_DECREF(pModule);
					fprintf(stderr, "Cannot convert array value");
					return 1;
				}
				PyTuple_SetItem(pYVec2, i, pValue); //
			}

			//Set the argument tuple to contain the two input tuples
			PyTuple_SetItem(pArgTuple1, 0, pXVec);
			PyTuple_SetItem(pArgTuple1, 1, pYVec1);
			PyTuple_SetItem(pArgTuple2, 0, pXVec);
			PyTuple_SetItem(pArgTuple2, 1, pYVec2);

			PyTuple_SetItem(pArgTuple3,0,pArgTuple1);
			PyTuple_SetItem(pArgTuple3,1,pArgTuple2);

			//Call the python function
			pValue = PyObject_CallObject(pFunc, pArgTuple3);
			
			Py_DECREF(pArgTuple1);
			Py_DECREF(pArgTuple2);
			Py_DECREF(pArgTuple3);

			Py_DECREF(pXVec);
			Py_DECREF(pYVec1);
			Py_DECREF(pYVec2);

			 if (pValue != NULL) {
				Py_DECREF(pValue);
			}

			//Some error catching
			else {
				Py_DECREF(pFunc);
				Py_DECREF(pModule);

				PyErr_Print();
				fprintf(stderr,"Call failed\n");
				return 1;
			}
		}
		else {
			if (PyErr_Occurred())
				PyErr_Print();
			fprintf(stderr, "Cannot find function" );
		}
		Py_XDECREF(pFunc);
		Py_DECREF(pModule);
	}
	else {
		PyErr_Print();
		fprintf(stderr, "Failed to load ");
		return 1;
	}

  	Py_Finalize();
  	return 0;
	}
}
