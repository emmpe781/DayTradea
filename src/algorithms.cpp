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

	//Pekar på min portfölj
	Portfolio::portfolionode *tmpPortfolio = portfolio_p->curPortfolio;

	//Pekar på min första aktie i portföljen


	Portfolio::portfolionode::stockinfo *tmpStock = tmpPortfolio->curStock;


	Stock::node *stock = omxS30_p->firstStockDate;
	cout << "stockdate: " <<  stock->date << endl;
	//Kanske måste skicka in referensen till portfolio_p
	portfolio_p->buy2(omxS30_p ,portfolio_p->portfolioMoney, stock->date);
	//Nu har jag handlat vissa aktier, dags att gå igenom värdet för portföljen!

	//tmpPortfolio->curStock = tmpPortfolio->curStock->next;
	//tmpPortfolio->curStock = tmpPortfolio->curStock->next;
	while(tmpPortfolio->curStock != NULL){
		cout << "sven date: " << tmpPortfolio->date << endl;
		cout << "name: " << tmpPortfolio->curStock->name << endl;
		cout << "nr of stocks: " << tmpPortfolio->curStock->nrOfStocks << endl;
		tmpPortfolio->curStock = tmpPortfolio->curStock->next;
	}
	//portfolio_p->buy(*omxS30_p, 1, stock->date);


	while(stock != lastStockDate){

		//cout << stock->date << endl;
		/*



		if (stock->bearBull == 1800){

			cout << "BULL Handla!" << endl;
		}

		else {
			cout << "BEAR Handla inte!" << endl;
		}



		//Uppdatera aktievärdet från föregående varv:
		tmpPortfolio->totalValue =
			tmpStock->stockValue * tmpStock->nrOfStocks + portfolio_p->portfolioMoney;


		cout << "Portfolio->TotalValue: " << tmpPortfolio->totalValue << endl;
		cout << "Portfolio->stockValue: " << tmpStock->stockValue << endl;
		cout << "portfolio_p->portfolioMoney: " << portfolio_p->portfolioMoney << endl;
		*/
		stock=stock->next;
	}

}

Algorithms::~Algorithms() {
	// TODO Auto-generated destructor stub
}
