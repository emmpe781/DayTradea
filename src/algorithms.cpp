/*
 * algorithms.cpp
 *
 *  Created on: 20 sep. 2017
 *      Author: Otur1337
 */

#include "algorithms.h"
#include "Portfolio.h"
#include "Stock.h"
using namespace std;
const Stock::node * lastStockDate = NULL;

Algorithms::Algorithms() {
	// TODO Auto-generated constructor stub

}

void Algorithms::Buy_BearBull(Portfolio_p portfolio_p, Stock_p omxS30_p) {

	//Hur ska algen fungera?
	//1 loopa igenom alla datum i index
	//2 när index ligger i bull -> var 100 % investerad
	//3 när index ligger i bear -> var 0 & investerad

	//The amount of startingcash in portfolio.


	Stock::node *stock = omxS30_p->firstStockDate;

	portfolio_p->buy2(omxS30_p ,portfolio_p->money, stock->date);
	portfolio_p->buy(*omxS30_p, 1, stock->date);

	while(stock != lastStockDate){



		if (stock->bearBull == 1800){

			cout << "BULL Handla!" << endl;
		}

		else {
			cout << "BEAR Handla inte!" << endl;
		}

		//port_p->buy(*stock_p, 1, stocktmp->date);

		/*if (stocktmp->bearBull == 1800){
			port_p->buy(*stock_p,1,stocktmp->date);
			cout << stocktmp->date << endl;
			cout << "BULL" << endl;
		}
		if (stocktmp->bearBull == 10){
			port_p->sell(*stock_p,1,stocktmp->date);
			cout << stocktmp->date << endl;
			cout << "BEAR" << endl;
		}*/

		stock=stock->nextDate;
	}
}

Algorithms::~Algorithms() {
	// TODO Auto-generated destructor stub
}
