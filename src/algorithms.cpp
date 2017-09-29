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


Algorithms::Algorithms() {
	// TODO Auto-generated constructor stub

}

void Algorithms::Buy_BearBull(Portfolio* port_p,Stock* stock_p) {

	Stock::node *stocktmp = stock_p->head;

	while(stocktmp != NULL){
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

	stocktmp=stocktmp->next;
	}
}

Algorithms::~Algorithms() {
	// TODO Auto-generated destructor stub
}

