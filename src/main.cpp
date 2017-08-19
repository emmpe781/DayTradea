//#include "matplotlib-cpp-master/matplotlibcpp.h"
//namespace plt = matplotlibcpp;
#include <list>
#include <string>
#include <iostream>
#include "Portfolio.h"
#include <fstream>

using namespace std;

int main() {

	Stock omx30;
	Stock volvo;
	Stock portfolio;

	string fname_portfolio="data/stockdata_Portfolio_fill.dat";
    string fname_omx30="data/stockdata_OMX30_1991-05-31_2017-07-03fill.dat";
    string fname_volvo="data/stockdata_VOLVO_1991-05-31_2017-07-03fill.dat";

    ReadFile a;
    a.Read(fname_omx30,omx30);
    a.Read(fname_volvo,volvo);
    a.Read(fname_portfolio,portfolio);


	Portfolio portfolio1(portfolio,"2016-12-11");
	portfolio1.buy(portfolio,3,"2016-12-30");
	portfolio1.buy(omx30,4,"2017-01-04");
	portfolio1.Print();



	return 0;
}
