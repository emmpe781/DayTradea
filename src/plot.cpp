/*
 * ReadFile.cpp
 *
 *  Created on: 3 juni 2017
 *      Author: Otur1337
 */
#pragma once

#include "plot.h"
#include "portfolio.h"
#include "stock.h"
#include "matplotlibcpp.h"
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

#if __cplusplus > 199711L || _MSC_VER > 1800
#include <functional>
#endif

#include <Python.h>

#if PY_MAJOR_VERSION >= 3
#define PyString_FromString PyUnicode_FromString
#endif

namespace plt = matplotlibcpp;
using namespace std;
PyObject *pFileName,*pModule;
PyObject *pFuncAppendList,*pFuncPlot;
PyObject *pArgTuple,*pArgTuple3, *pValue, *pValue1,*pArgEmpty, *pXVec, *pYVec, *pYVec2;

Plot::Plot(void)
{
    cout << "Plotting " << '\n';

   	Py_Initialize();
 	PyObject *sys = PyImport_ImportModule("sys");
	PyObject *path = PyObject_GetAttrString(sys, "path");
	PyList_Append(path, PyString_FromString("."));
	
	pFileName = PyString_FromString("pythonToEmbed");   //Get the name of the module
	pModule = PyImport_Import(pFileName);     //Get the module
	Py_DECREF(pFileName);

	if (pModule != NULL) {
		pFuncAppendList = PyObject_GetAttrString(pModule,"appendList");
		pFuncPlot = PyObject_GetAttrString(pModule, "plotStdVectors"); 
		if (pFuncAppendList && pFuncPlot && PyCallable_Check(pFuncAppendList) && PyCallable_Check(pFuncPlot)) {
			cout << "lyckades ladda" << endl;
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
}

void Plot::Append_One_Portfolio(Portfolio port)
{
	pArgTuple = PyTuple_New(3);	

	Portfolio::portfolionode *tmp = port.head;
	Portfolio::portfolionode::stockinfo *infotmp = tmp->head;

	int n=port.portfoliolength;

	vector<double> portfolio_value_1(n,2000);
	vector<string> t(n);
	int i = 0;
    while(tmp!= NULL){
		t.at(i) = tmp->date;
		while(infotmp!=NULL){
			if (infotmp->name=="portfolio value"){
				portfolio_value_1.at(i) = infotmp->volume;
				}
			infotmp=infotmp->next;
		}
		i=i+1;
    	infotmp=tmp->head;
		tmp=tmp->next;
   		}

	//Transfer the C++ vector to a python tuple
	pXVec = PyTuple_New(t.size());	
	for (i = 0; i < t.size(); ++i) {
		pValue = PyString_FromString(t[i].c_str());
		if (!pValue) {
			Py_DECREF(pXVec);
			Py_DECREF(pModule);
			fprintf(stderr, "Cannot convert array value");
			//return 1;
		}
		PyTuple_SetItem(pXVec, i, pValue);
	}

	//Transfer the other C++ vector to a python tuple
	pYVec = PyTuple_New(portfolio_value_1.size());	
	for (i = 0; i < portfolio_value_1.size(); ++i) {
		pValue = PyFloat_FromDouble(portfolio_value_1[i]);
		if (!pValue) {
			Py_DECREF(pYVec);
			Py_DECREF(pModule);
			fprintf(stderr, "Cannot convert array value");
			//return 1;
		}
		PyTuple_SetItem(pYVec, i, pValue); //
	}

	PyTuple_SetItem(pArgTuple, 0, PyString_FromString("close"));
	PyTuple_SetItem(pArgTuple, 1, pXVec);
	PyTuple_SetItem(pArgTuple, 2, pYVec);
		
	pValue1 = PyObject_CallObject(pFuncAppendList,pArgTuple);

	Py_DECREF(pArgTuple);
	Py_DECREF(pXVec);
	Py_DECREF(pYVec);
}


void Plot::Append_One_Stock(Stock stock)
{
	pArgTuple = PyTuple_New(3);	

	int n=stock.stocklength;

	Stock::node *stocktmp = stock.head;

   	vector<double> close_value_stock(n,stock.tail->close);
   	vector<double> ma200_stock(n,stock.tail->ma200);
   	vector<double> bearbull(n,stock.tail->bearBull);
   	vector<string> t(n);

   	int i = 0;
    while(stocktmp != NULL){
   		t.at(i) = stocktmp->date;
       	close_value_stock.at(i) = stocktmp->close;
    	//z.at(i) = stocktmp->est;
        ma200_stock.at(i) = stocktmp->ma200;
        bearbull.at(i) = stocktmp->bearBull;
   		i=i+1;
   		stocktmp=stocktmp->next;
    }
	

	//Transfer the C++ vector to a python tuple
	pXVec = PyTuple_New(t.size());	
	for (i = 0; i < t.size(); ++i) {
		pValue = PyString_FromString(t[i].c_str());
		if (!pValue) {
			Py_DECREF(pXVec);
			Py_DECREF(pModule);
			fprintf(stderr, "Cannot convert array value");
			//return 1;
		}
		PyTuple_SetItem(pXVec, i, pValue);
	}

	//Transfer the other C++ vector to a python tuple
	pYVec = PyTuple_New(close_value_stock.size());	
	for (i = 0; i < close_value_stock.size(); ++i) {
		pValue = PyFloat_FromDouble(close_value_stock[i]);
		if (!pValue) {
			Py_DECREF(pYVec);
			Py_DECREF(pModule);
			fprintf(stderr, "Cannot convert array value");
			//return 1;
		}
		PyTuple_SetItem(pYVec, i, pValue); //
	}

	PyTuple_SetItem(pArgTuple, 0, PyString_FromString("close"));
	PyTuple_SetItem(pArgTuple, 1, pXVec);
	PyTuple_SetItem(pArgTuple, 2, pYVec);
		
	pValue1 = PyObject_CallObject(pFuncAppendList,pArgTuple);

	Py_DECREF(pArgTuple);
	Py_DECREF(pXVec);
	Py_DECREF(pYVec);
}


void Plot::Plot_all(Portfolio port1,Portfolio port2,Stock stock)
{
	Append_One_Portfolio(port1);
	Append_One_Portfolio(port2);

	Append_One_Stock(stock);

    pValue = PyObject_CallObject(pFuncPlot, pArgEmpty);

}    


Plot::~Plot()
{
	  	Py_Finalize();
}

