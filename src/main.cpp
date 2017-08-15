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

    string fname_omx30="data/stockdata_OMX30_1986-09-30_2017-03-24.dat";
    string fname_volvo="data/stockdata_VOLVO_1986-09-30_2017-03-24.dat";

    ReadFile a;
    a.Read(fname_omx30,omx30);
    a.Read(fname_volvo,volvo);
    //omx30.buyStock(2,"2015-11-30");
	//omx30.Print();




	Portfolio portfolio1;
	//portfolio1.portfolioname = "Portfolio_1";
	cout << "#1"<< endl;
	portfolio1.buyStock(omx30,1,"2016-10-11");
	cout << "#2"<< endl;
	//portfolio1.buyStock(omx30,3,"2016-12-11");

	//portfolio1.add_stock(volvo);


	portfolio1.Print();

	return 0;
}
