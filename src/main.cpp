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
	Stock test;


	string fname_testfile="data/stockdata_Portfolio_fill.dat";
    string fname_omx30="data/stockdata_OMX30_1991-05-31_2017-07-03fill.dat";
    string fname_volvo="data/stockdata_VOLVO_1991-05-31_2017-07-03fill.dat";

    ReadFile a;
    a.Read(fname_omx30,omx30);
    a.Read(fname_volvo,volvo);
    a.Read(fname_testfile,test);
	Stock portfolio_time = test;


	Portfolio portfolio1(portfolio_time,"2004-12-11");
	cout << "adding 100 000 SEK" << endl;
	portfolio1.add_to_bank(110,"2004-12-30");
	portfolio1.buy(omx30,1,"2005-01-05");

	portfolio1.Print();



	return 0;
}
