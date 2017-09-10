/*
 * ReadFile.cpp
 *
 *  Created on: 3 juni 2017
 *      Author: Otur1337
 */
#include "plot.h"
#include "portfolio.h"
#include "stock.h"
#include "matplotlibcpp.h"
#include <list>
#include <iostream>
#include <fstream>
#include <string>

namespace plt = matplotlibcpp;
using namespace std;

Plot1::Plot1(void)
{
    cout << "Plotting " << '\n';
}
void Plot1::plotta(Portfolio port,Stock stock)
{

	cout << "PRINT: " << endl;
	Portfolio::portfolionode *tmp = port.head;
	Portfolio::portfolionode::stockinfo *infotmp = tmp->head;


	//int n=2130;
	int n=8000;
	vector<int> x(n);
	vector<double> y(n);
	vector<string> t(n);
	int i = 0;
    while(tmp!= NULL){
		x.at(i) = i;
		t.at(i) = tmp->date;
		while(infotmp!=NULL){
			if (infotmp->name=="portfolio value"){
				y.at(i) = infotmp->volume;
				}
			infotmp=infotmp->next;
		}
		i=i+1;
    	infotmp=tmp->head;
		tmp=tmp->next;
   }

	Stock::node *stocktmp = stock.head;
	cout << "PRINT: " << endl;

	vector<int> a(n);
	vector<double> b(n);
	vector<string> c(n);
	int j = 0;
    while(stocktmp!= NULL){
		a.at(j) = j;
		c.at(j) = stocktmp->date;
		b.at(j) = stocktmp->close;
		j=j+1;
		stocktmp=stocktmp->next;
   }


	//	plt::xticks()
	//plt::xticks(x,t);
	plt::plot(x,y, "k-");
	plt::plot(a,b, "r-");

    //plt::plot({"1","2","3","4"},{1,3,2,4},"k");
	//plt::grid(true);
	plt::title("Portfolio");
	//plt::tight_layout();
	plt::save("./portfolio.png");
	plt::show();

}

Plot1::~Plot1()
{
}

