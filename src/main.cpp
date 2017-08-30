//#include "matplotlib-cpp-master/matplotlibcpp.h"
#include <list>
#include <string>
#include <iostream>
#include "Portfolio.h"
#include <fstream>


using namespace std;
//namespace plt = matplotlibcpp;


int main() {
	ReadFile rf;
	Portfolio ImbaPortfolio(rf,"2004-12-11");


	Stock omx30;
    string fname_omx30="../data/stockdata_OMX30_1991-05-31_2017-07-03fill.dat";
    rf.Read(fname_omx30,omx30);

	/*Stock volvo;
    string fname_volvo="data/stockdata_VOLVO_1991-05-31_2017-07-03fill.dat";
    rf.Read(fname_volvo,volvo);*/

	cout << "adding 100 000 SEK" << endl;
	ImbaPortfolio.add_to_bank(100000,"2016-12-30");
	
	ImbaPortfolio.buy(omx30,584,"2017-01-05");

	ImbaPortfolio.Print();


	// plot(y) - the x-coordinates are implicitly set to [0,1,...,n)
	//plt::plot({1,2,3,4}); 
	
	// Prepare data for parametric plot.
	/*int n = 5000; // number of data points
	vector<double> x(n),y(n); 
	for(int i=0; i<n; ++i) {
		double t = 2*M_PI*i/n;
		x.at(i) = 16*sin(t)*sin(t)*sin(t);
		y.at(i) = 13*cos(t) - 5*cos(2*t) - 2*cos(3*t) - cos(4*t);
	}

	// plot() takes an arbitrary number of (x,y,format)-triples. 
	// x must be iterable (that is, anything providing begin(x) and end(x)),
	// y must either be callable (providing operator() const) or iterable. 
	plt::plot(x, y, "r-", x, [](double d) { return 12.5+abs(sin(d)); }, "k-");


	// show plots
	plt::show();*/

	return 0;


}
