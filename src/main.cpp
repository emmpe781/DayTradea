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
	Portfolio Reference("1987-03-05");
	Reference.add_to_bank(12979,"1987-03-15");

	Portfolio ImbaPortfolio("1987-03-05");
	ImbaPortfolio.add_to_bank(12979,"1987-03-15");

	Algorithms Algo;
	ReadFile rf; //TODO: create namespace instead of object

	Stock omx30;
	string fname_omx30="../data/stockdata_OMX30_1986-09-30_2017-03-24.dat";
	rf.Read(fname_omx30,&omx30);
	rf.PopulateStock(&omx30);

	Reference.buy(omx30,100,"1987-03-17");
	ImbaPortfolio.buy(omx30,100,"1987-03-17");

	Algo.Buy_BearBull(&ImbaPortfolio,&omx30);
	Plot plt1;
	//plt1.PlotNodes(omx30,"bearbull");
	plt1.Plot_port(ImbaPortfolio,Reference);


	return 0;


}


//OLD STUFF

/*Stock volvo;
string fname_volvo="data/stockdata_VOLVO_1991-05-31_2017-07-03fill.dat";
rf.Read(fname_volvo,volvo);*/

//cout << "adding 100 000 SEK" << endl;

//ImbaPortfolio.buy(omx30,1,"2012-03-06");

//

//Plot plt1;
//plt1.Plot_port(ImbaPortfolio,omx30expected);

//omx30.Plot();

//ImbaPortfolio.Plot();
