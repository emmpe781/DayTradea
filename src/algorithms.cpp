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
	bool firstbear=false;
	bool firstbull=true;

	while(stocktmp != NULL){
	if (stocktmp->bearBull == 1800 && firstbull==false){
		port_p->buy(*stock_p,12979,stocktmp->date);
		firstbull=true;
		firstbear=false;
	}
	if (stocktmp->bearBull == 10 && firstbear==false){
		port_p->sell(*stock_p,12979,stocktmp->date);

		firstbull=false;
		firstbear=true;
	}

	stocktmp=stocktmp->next;
	}
	//port_p->buy(*stock_p,40,"2003-03-17");
	//port_p->add_to_bank(1000,"2000-03-15");
}

Algorithms::~Algorithms() {
	// TODO Auto-generated destructor stub
}

