#include <list>
#include <string>
#include <iostream>
#include "Portfolio.h"
#include <fstream>
#include "plot.h"
#include "algorithms.h"
#include "ReadFile.h"
using namespace std;

int main() {
	float startValue = 13370;
	//string startdate = "1987-03-05";
	string startdate = "2016-09-17";
	Portfolio Reference(startdate);
	Reference.add_to_bank(startValue,startdate);






	//
	//ImbaPortfolio.add_to_bank(1000,startdate);


	ReadFile rf; //TODO: create namespace instead of object

	Stock omx30;
	string fname_omx30="../data/stockdata_OMX30_1986-09-30_2017-03-24.dat";
	rf.Read(fname_omx30,&omx30,startdate);
	rf.PopulateStock(&omx30);

	Reference.buy(omx30,1,startdate);
	//ImbaPortfolio.buy(omx30,1,startdate);


	//Min portf�lj b�rjar:
	Portfolio ImbaPortfolio(startdate);
	ImbaPortfolio.setStartValue(startValue);

	//Min algh. startar
	Algorithms Algo;
	Algo.Buy_BearBull(&ImbaPortfolio ,&omx30);

//	Plot plt1;
//	plt1.Plot_all(ImbaPortfolio,Reference,omx30);


	return 0;
}
