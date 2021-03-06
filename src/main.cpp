#include <list>
#include <string>
#include <iostream>
#include "readfile.h"
#include "startthreads.h"
#include "Portfolio.h"
#include "algorithms.h"
#include "plot.h"
#include <fstream>
#include <cstdlib>
#include <pthread.h>
#include <Python.h>
#include <fstream>
#include <windows.h>
#include <vector>
#define NUM_THREADS 1

void *StartPython(void *threadid) {
	Start th;
    th.Start_Python();
    pthread_exit(NULL);
}

int main () {
    string rawData;

    bool pushed = false;
	pthread_t threads[NUM_THREADS];
	int i=1;
	pthread_create(&threads[1], NULL, StartPython, (void *)i);
	Sleep(3000);

	while (!pushed)
	{
		try{
			ifstream myfile ("Buttonpushed.txt");
			getline (myfile,rawData);
			if(rawData == "PUSHED"){
				pushed = true;
			}
		}
		catch (int e) 
		{
			    cout << "An exception occurred. Exception Nr. "  << '\n';
		}
	}
	Sleep(200);
	ReadFile1 rf;
   	vector< string > arr;

	rf.ReadTicks(&arr);

	for (int x = 0; x != arr.size(); ++x)
	{
	     cout << arr[x] << "- subscripting" << endl;
	}

	string startdate = "1987-03-05";
	Portfolio Reference(startdate);
	Reference.add_to_bank(100,startdate);

	Portfolio ImbaPortfolio(startdate);
	ImbaPortfolio.add_to_bank(100,startdate);

	Algorithms Algo;
	
	Stock omx30;
	string fname_omx30="../data/stockdata_OMX30_1986-10-01_2017-10-18_fill.dat";
	rf.Read(fname_omx30,&omx30,startdate);
	rf.PopulateStock(&omx30);

	Reference.buy(omx30,1,startdate);
	ImbaPortfolio.buy(omx30,1,startdate);



	//Algo.Buy_BearBull(&ImbaPortfolio,&omx30);
	//Plot plt1;
	//plt1.Plot_all(ImbaPortfolio,Reference,omx30);
	pthread_exit(NULL);

	return 0;
}

