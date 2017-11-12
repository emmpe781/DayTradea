#include <list>
#include <string>
#include <iostream>
#include "startthreads.h"
#include "Portfolio.h"
#include "algorithms.h"
#include "plot.h"
#include "ReadFile.h"
#include <fstream>
#include <cstdlib>
#include <pthread.h>
#include <Python.h>
#define NUM_THREADS 1

void *StartPython(void *threadid) {
	Start th;
    th.Start_Python();
    pthread_exit(NULL);
}

int main () {
    cout << "threadPython starting..." << endl;

	pthread_t threads[NUM_THREADS];
	int i=1;
    pthread_create(&threads[1], NULL, StartPython, (void *)i);

    cout << "BUTTON PUSHED" << endl;

	pthread_exit(NULL);

/*	string startdate = "1987-03-05";
	Portfolio Reference(startdate);
	Reference.add_to_bank(100,startdate);

	Portfolio ImbaPortfolio(startdate);
	ImbaPortfolio.add_to_bank(100,startdate);

	Algorithms Algo;
	ReadFile rf2; //TODO: create namespace instead of object

	Stock omx30;
	string fname_omx30="../data/stockdata_OMX30_1986-10-01_2017-10-18_fill.dat";
	rf2.Read(fname_omx30,&omx30,startdate);
	rf2.PopulateStock(&omx30);

	Reference.buy(omx30,1,startdate);
	ImbaPortfolio.buy(omx30,1,startdate);

	//Algo.Buy_BearBull(&ImbaPortfolio,&omx30);
	Plot plt1;
	plt1.Plot_all(ImbaPortfolio,Reference,omx30);
*/
	return 0;
}

