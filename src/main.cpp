#include <list>
#include <string>
#include <iostream>
#include "Portfolio.h"
#include <fstream>
#include "plot.h"
#include "ReadFile.h"
using namespace std;

int main() {
	Portfolio ImbaPortfolio("2002-03-05");

	ReadFile rf; //TODO: create namespace instead of object

	Stock omx30;
	string fname_omx30="../data/stockdata_OMX30_1991-05-31_2017-07-03fill.dat";
	rf.Read(fname_omx30,&omx30);


	rf.ExpectedValue("2002-03-06",&omx30,7.5);
	rf.Mean("2002-03-06",&omx30,200);

	//rf.BearBull(omx30mean200);

	Plot plt1;
	plt1.PlotNodes(omx30,"ma200");


    /*Stock volvo;
    string fname_volvo="data/stockdata_VOLVO_1991-05-31_2017-07-03fill.dat";
    rf.Read(fname_volvo,volvo);*/

	//cout << "adding 100 000 SEK" << endl;
	//ImbaPortfolio.add_to_bank(100,"2011-03-15");
	
	//ImbaPortfolio.buy(omx30,1,"2012-03-06");

	//ImbaPortfolio.Print();

	//Plot plt1;
	//plt1.Plot_port(ImbaPortfolio,omx30expected);

	//omx30.Plot();

	//ImbaPortfolio.Plot();


	return 0;


}
