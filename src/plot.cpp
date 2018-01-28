/*
 * ReadFile.cpp
 *
 *  Created on: 3 juni 2017
 *      Author: Otur1337
 */
#include <cmath>
#include <Python.h>
#include "plot.h"
#include "portfolio.h"
#include "stock.h"
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


#if PY_MAJOR_VERSION >= 3
#define PyString_FromString PyUnicode_FromString
#endif

using namespace std;
PyObject *pFileName,*pModule;
PyObject *pFuncAppendList,*pFuncPlot;
PyObject *pArgTuple, *pArgTuple3, *pValue, *pValue1,*pArgEmpty, *pXVec, 
*pYVec, *pYVec2,*pYVecEst,*pVecNorm,*pYVecMa200,*pYVecMa50,*pYVecBearBull, *pArgTuplebearbull,*pArgTupleNorm,*pArgTuplema200,*pArgTuplema50,*pArgTupleest;
	
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
	pArgTuple = PyTuple_New(5);	

	Portfolio::portfolionode *tmp = port.curPortfolio;
	Portfolio::portfolionode::stockinfo *infotmp = tmp->curStock;

	int n=port.portfoliolength;

	vector<double> portfolio_value_1(n,2000);
	vector<string> t(n);
	int i = 0;
    while(tmp!= NULL){
		t.at(i) = tmp->date;
		//portfolio_value_1.at(i)= tmp->portfolioValue;
		portfolio_value_1.at(i)= tmp->normValue;
		i=i+1;
    	infotmp=tmp->curStock;
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

	PyTuple_SetItem(pArgTuple, 0, PyString_FromString("portfolio"));
	PyTuple_SetItem(pArgTuple, 1, pXVec);
	PyTuple_SetItem(pArgTuple, 2, pYVec);
	PyTuple_SetItem(pArgTuple, 3, PyString_FromString("close"));
	PyTuple_SetItem(pArgTuple, 4, PyString_FromString("show"));
		
	pValue1 = PyObject_CallObject(pFuncAppendList,pArgTuple);

	Py_DECREF(pArgTuple);
	Py_DECREF(pXVec);
	Py_DECREF(pYVec);
}


void Plot::Append_One_Stock(Stock stock)
{
	pArgTuple = PyTuple_New(5);	
	pArgTuplebearbull = PyTuple_New(5);
	pArgTuplema50 = PyTuple_New(5);	
	pArgTuplema200 = PyTuple_New(5);	
	pArgTupleest = PyTuple_New(5);	
	pArgTupleNorm = PyTuple_New(5);	

	int n=stock.stockLength;

	Stock::dayInfo *stocktmp = stock.head;

   	vector<double> close_value_stock(n,stock.tail->close);
	vector<double> norm_value_stock(n,stock.tail->norm);
   	vector<double> est_stock(n,stock.tail->est);
   	vector<double> ma50_stock(n,stock.tail->ma50);
   	vector<double> ma200_stock(n,stock.tail->ma200);
   	vector<double> bearbull(n,stock.tail->bearBull);
   	vector<string> t(n);

   	int i = 0;
    while(stocktmp != NULL){
	   	t.at(i) = stocktmp->date;
	    close_value_stock.at(i) = stocktmp->close;
	    norm_value_stock.at(i) = stocktmp->norm;
	    est_stock.at(i) = stocktmp->est;
	    ma200_stock.at(i) = stocktmp->ma200;
	    ma50_stock.at(i) = stocktmp->ma50;
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

	PyTuple_SetItem(pArgTuple, 0, PyString_FromString("stock"));
	PyTuple_SetItem(pArgTuple, 1, pXVec);
	PyTuple_SetItem(pArgTuple, 2, pYVec);
	PyTuple_SetItem(pArgTuple, 3, PyString_FromString("close"));
	PyTuple_SetItem(pArgTuple, 4, PyString_FromString("legendonly"));

	pValue1 = PyObject_CallObject(pFuncAppendList,pArgTuple);


	//Transfer the other C++ vector to a python tuple
	pVecNorm = PyTuple_New(norm_value_stock.size());	
	for (i = 0; i < norm_value_stock.size(); ++i) {
		pValue = PyFloat_FromDouble(norm_value_stock[i]);
		if (!pValue) {
			Py_DECREF(pVecNorm);
			Py_DECREF(pModule);
			fprintf(stderr, "Cannot convert array value");
			//return 1;
		}
		PyTuple_SetItem(pVecNorm, i, pValue); //
	}

	PyTuple_SetItem(pArgTupleNorm, 0, PyString_FromString("stock"));
	PyTuple_SetItem(pArgTupleNorm, 1, pXVec);
	PyTuple_SetItem(pArgTupleNorm, 2, pVecNorm);
	PyTuple_SetItem(pArgTupleNorm, 3, PyString_FromString("norm"));
	PyTuple_SetItem(pArgTupleNorm, 4, PyString_FromString("show"));
	pValue1 = PyObject_CallObject(pFuncAppendList,pArgTupleNorm);


	//Transfer the other C++ vector to a python tuple
	pYVecMa200 = PyTuple_New(ma200_stock.size());	
	for (i = 0; i < ma200_stock.size(); ++i) {
		pValue = PyFloat_FromDouble(ma200_stock[i]);
		if (!pValue) {
			Py_DECREF(pYVecMa200);
			Py_DECREF(pModule);
			fprintf(stderr, "Cannot convert array value");
			//return 1;
		}
		PyTuple_SetItem(pYVecMa200, i, pValue); //
	}
	
	PyTuple_SetItem(pArgTuplema200, 0, PyString_FromString("stock"));
	PyTuple_SetItem(pArgTuplema200, 1, pXVec);
	PyTuple_SetItem(pArgTuplema200, 2, pYVecMa200);
	PyTuple_SetItem(pArgTuplema200, 3, PyString_FromString("Ma200"));
	PyTuple_SetItem(pArgTuplema200, 4, PyString_FromString("legendonly"));
	pValue1 = PyObject_CallObject(pFuncAppendList,pArgTuplema200);


	//Transfer the other C++ vector to a python tuple
	pYVecMa50 = PyTuple_New(ma50_stock.size());	
	for (i = 0; i < ma50_stock.size(); ++i) {
		pValue = PyFloat_FromDouble(ma50_stock[i]);
		if (!pValue) {
			Py_DECREF(pYVecMa50);
			Py_DECREF(pModule);
			fprintf(stderr, "Cannot convert array value");
			//return 1;
		}
		PyTuple_SetItem(pYVecMa50, i, pValue); //
	}
	
	PyTuple_SetItem(pArgTuplema50, 0, PyString_FromString("stock"));
	PyTuple_SetItem(pArgTuplema50, 1, pXVec);
	PyTuple_SetItem(pArgTuplema50, 2, pYVecMa50);
	PyTuple_SetItem(pArgTuplema50, 3, PyString_FromString("Ma50"));
	PyTuple_SetItem(pArgTuplema50, 4, PyString_FromString("legendonly"));

	pValue1 = PyObject_CallObject(pFuncAppendList,pArgTuplema50);

	//Transfer the other C++ vector to a python tuple
	pYVecBearBull = PyTuple_New(bearbull.size());	
	for (i = 0; i < bearbull.size(); ++i) {
		pValue = PyFloat_FromDouble(bearbull[i]);
		if (!pValue) {
			Py_DECREF(pYVecBearBull);
			Py_DECREF(pModule);
			fprintf(stderr, "Cannot convert array value");
			//return 1;
		}
		PyTuple_SetItem(pYVecBearBull, i, pValue); //
	}
	PyTuple_SetItem(pArgTuplebearbull, 0, PyString_FromString("stock"));
	PyTuple_SetItem(pArgTuplebearbull, 1, pXVec);
	PyTuple_SetItem(pArgTuplebearbull, 2, pYVecBearBull);
	PyTuple_SetItem(pArgTuplebearbull, 3, PyString_FromString("Bear-Bull"));
	PyTuple_SetItem(pArgTuplebearbull, 4, PyString_FromString("legendonly"));
	pValue1 = PyObject_CallObject(pFuncAppendList,pArgTuplebearbull);

	//Transfer the other C++ vector to a python tuple
	pYVecEst = PyTuple_New(est_stock.size());	
	for (i = 0; i < est_stock.size(); ++i) {
		pValue = PyFloat_FromDouble(est_stock[i]);
		if (!pValue) {
			Py_DECREF(pYVecEst);
			Py_DECREF(pModule);
			fprintf(stderr, "Cannot convert array value");
			//return 1;
		}
		PyTuple_SetItem(pYVecEst, i, pValue); //
	}

	PyTuple_SetItem(pArgTupleest, 0, PyString_FromString("stock"));
	PyTuple_SetItem(pArgTupleest, 1, pXVec);
	PyTuple_SetItem(pArgTupleest, 2, pYVecEst);
	PyTuple_SetItem(pArgTupleest, 3, PyString_FromString("est"));
	PyTuple_SetItem(pArgTupleest, 4, PyString_FromString("legendonly"));
	pValue1 = PyObject_CallObject(pFuncAppendList,pArgTupleest);

	Py_DECREF(pArgTuplema200);
	Py_DECREF(pArgTuplema50);
	Py_DECREF(pArgTuplebearbull);
	Py_DECREF(pArgTupleest);
	Py_DECREF(pArgTuple);
	Py_DECREF(pArgTupleNorm);
	Py_DECREF(pXVec);
	Py_DECREF(pYVec);
}


void Plot::Plot_all(Portfolio port1, Portfolio port2, Stock stock)
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

