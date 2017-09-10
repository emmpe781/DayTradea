#include <list>
#include <string>
#include <iostream>
#include "Portfolio.h"
#include <fstream>
#include "plot.h"

using namespace std;

int main() {

	ReadFile rf;
	Portfolio ImbaPortfolio(rf,"2011-03-13");


	Stock omx30;
    string fname_omx30="../data/stockdata_OMX30_1991-05-31_2017-07-03fill.dat";
    rf.Read(fname_omx30,omx30);

	/*Stock volvo;
    string fname_volvo="data/stockdata_VOLVO_1991-05-31_2017-07-03fill.dat";
    rf.Read(fname_volvo,volvo);*/

	cout << "adding 100 000 SEK" << endl;
	ImbaPortfolio.add_to_bank(100,"2011-03-15");
	
	ImbaPortfolio.buy(omx30,1,"2012-03-06");

	ImbaPortfolio.Print();

	Plot1 plt1;
	plt1.plotta(ImbaPortfolio,omx30);

	//omx30.Plot();

	//ImbaPortfolio.Plot();


	return 0;


}
