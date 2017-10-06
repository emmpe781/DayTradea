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


int runPython(std::vector<string> xvec,std::vector<double> yvec) {
	PyObject *pName, *pModule, *pFunc;
	PyObject *pArgTuple, *pValue, *pXVec, *pYVec;

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
			pArgTuple = PyTuple_New(2);

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
			pYVec = PyTuple_New(yvec.size());	
			for (i = 0; i < yvec.size(); ++i) {
				pValue = PyFloat_FromDouble(yvec[i]);
				if (!pValue) {
					Py_DECREF(pYVec);
					Py_DECREF(pModule);
					fprintf(stderr, "Cannot convert array value");
					return 1;
				}
				PyTuple_SetItem(pYVec, i, pValue); //
			}

			//Set the argument tuple to contain the two input tuples
			PyTuple_SetItem(pArgTuple, 0, pXVec);
			PyTuple_SetItem(pArgTuple, 1, pYVec);

			//Call the python function
			pValue = PyObject_CallObject(pFunc, pArgTuple);
			
			Py_DECREF(pArgTuple);
			Py_DECREF(pXVec);
			Py_DECREF(pYVec);

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
