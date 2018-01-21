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
	float startValue = 2500;
	//string startdate = "1986-10-05";
	string startdate = "1995-10-05";

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

	Stock indu_c;
	string fname_indu_c="../data/ticks/stockdata_INDU-C.dat";
	rf.Read(fname_indu_c,&indu_c,startdate);
	rf.PopulateStock(&indu_c);

	Stock inve_b;
	string fname_inve_b="../data/ticks/stockdata_INVE-B.dat";
	rf.Read(fname_inve_b,&inve_b,startdate);
	rf.PopulateStock(&inve_b);

	Stock lato_b;
	string fname_lato_b="../data/ticks/stockdata_LATO-B.dat";
	rf.Read(fname_lato_b,&lato_b,startdate);
	rf.PopulateStock(&lato_b);

	Stock lund_b;
	string fname_lund_b="../data/ticks/stockdata_LUND-B.dat";
	rf.Read(fname_lund_b,&lund_b,startdate);
	rf.PopulateStock(&lund_b);

	Stock ores;
	string fname_ores="../data/ticks/stockdata_ORES.dat";
	rf.Read(fname_ores,&ores,startdate);
	rf.PopulateStock(&ores);

	Stock rato_b;
	string fname_rato_b="../data/ticks/stockdata_RATO-B.dat";
	rf.Read(fname_rato_b,&rato_b,startdate);
	rf.PopulateStock(&rato_b);

	Stock svol_b;
	string fname_svol_b="../data/ticks/stockdata_SVOL-B.dat";
	rf.Read(fname_svol_b,&svol_b,startdate);
	rf.PopulateStock(&svol_b);

	//Min portfölj börjar:
	Portfolio ImbaPortfolio(startdate);
	ImbaPortfolio.portfolioname = "ImbaPortfolio";
	ImbaPortfolio.setStartValue(startValue);

	
	Algorithms Algo;
	//NROFSTOCKS definierad i stock.h
	Stock stockArray[NROFSTOCKS] = {bure, cred_a, indu_c, inve_b,  
									lato_b, lund_b, ores, rato_b, svol_b};


	Algo.Algo("CREATEINDEX",&ImbaPortfolio ,stockArray);
	rf.NormalizedPort(&ImbaPortfolio);
	Plot plt1;
	plt1.Plot_all(ImbaPortfolio,Reference,omx30);
	
	//Plot plt2;
	//plt2.Plot_all(ImbaPortfolio,Reference, rato_b);

	return 0;
}



