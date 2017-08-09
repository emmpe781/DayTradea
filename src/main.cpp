//#include "matplotlib-cpp-master/matplotlibcpp.h"
//namespace plt = matplotlibcpp;
#include <list>
#include <string>
#include <iostream>
#include "stock.h"
#include "readfile.h"
#include "modifystock.h"
#include <fstream>

using namespace std;

int main() {
	Stock omx30;
    string fname="data/stockdata_OMX30_1986-09-30_2017-03-24.dat";

    ReadFile a;
    a.Read(fname,omx30);

	omx30.buyStock(2,"2015-11-30");
	omx30.buyStock(4,"2015-12-08");
	omx30.sellStock(3,"2015-12-15");

	omx30.Print();

	return 0;
}
