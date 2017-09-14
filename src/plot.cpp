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
#include <stdarg.h>

namespace plt = matplotlibcpp;
using namespace std;

Plot::Plot(void)
{
    cout << "Plotting " << '\n';
}
void Plot::Plot_port(Portfolio port,Stock stock)
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

void Plot::Plot_stocks(Stock stock1,Stock stock2)
{
	Stock::node *stocktmp1 = stock1.head;

	cout << "PRINT: " << endl;

	int n=5100;

	vector<int> x(n,5000);
	vector<double> y(n,160);
	vector<string> t(n);
	int i = 0;
    while(stocktmp1!= NULL){
		x.at(i) = i;
		t.at(i) = stocktmp1->date;
		y.at(i) = stocktmp1->close;
		i=i+1;
		stocktmp1=stocktmp1->next;
    }

	Stock::node *stocktmp2 = stock2.head;
	cout << "PRINT: " << endl;

	vector<int> a(n,5000);
	vector<double> b(n,160);
	vector<string> c(n);
	int j = 0;
    while(stocktmp2!= NULL){
		a.at(j) = j;
		c.at(j) = stocktmp2->date;
		b.at(j) = stocktmp2->close;
		j=j+1;
		stocktmp2=stocktmp2->next;
   }


	//	plt::xticks()
	//plt::xticks(x,t);
	plt::plot(x,y, "k-");
	plt::plot(a,b, "r-");

    //plt::plot({"1","2","3","4"},{1,3,2,4},"k");
	//plt::grid(true);
	plt::title("Stocks");
	//plt::tight_layout();
	plt::save("./portfolio.png");
	plt::show();

}



Plot::~Plot()
{
}

