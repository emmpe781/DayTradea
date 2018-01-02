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
	float startValue = 250;
	string startdate = "1986-10-05";

	Portfolio Reference(startdate);
	Reference.setStartValue(startValue);

	ReadFile rf; //TODO: create namespace instead of object
	Stock omx30;
	string fname_omx30="../data/stockdata_OMX30_1986-09-30_2017-12-28_fill.dat";
	rf.Read(fname_omx30,&omx30,startdate);
	rf.PopulateStock(&omx30);

	Stock bure;
	string fname_bure="../data/ticks/stockdata_BURE.dat";
	rf.Read(fname_bure,&bure,startdate);
	rf.PopulateStock(&bure);

	Stock cred_a;
	string fname_cred_a="../data/ticks/stockdata_CRED-A.dat";
	rf.Read(fname_cred_a,&cred_a,startdate);
	rf.PopulateStock(&cred_a);

	//Min portfölj börjar:
	Portfolio ImbaPortfolio(startdate);
	ImbaPortfolio.portfolioname = "ImbaPortfolio";
	ImbaPortfolio.setStartValue(startValue);

	//Min algh. startar 
	Algorithms Algo;
	Algo.Algo("BEARBULL",&ImbaPortfolio ,&omx30); //borde skicka in const på omx30

	Plot plt1;
	plt1.Plot_all(ImbaPortfolio,Reference,omx30);

	return 0;
}



