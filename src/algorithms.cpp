/*
 * algorithms.cpp
 *
 *  Created on: 20 sep. 2017
 *      Author: Otur1337
 */

#include "algorithms.h"
#include "Portfolio.h"
#include "Stock.h"
#include "string"
using namespace std;
const Stock::node * lastStockDate = NULL;

Algorithms::Algorithms() {
	// TODO Auto-generated constructor stub

}

void Algorithms::Buy_BearBull(Portfolio_p portfolio_p, Stock_p omxS30_p) {
	//Hur ska algen fungera?
	//1 loopa igenom alla datum i index
	//2 n�r index ligger i bull -> var 100 % investerad
	//3 n�r index ligger i bear -> var 0 & investerad

	//Pekar p� noden f�r mitt f�rsta datum i portf�ljen
	Portfolio::portfolionode *tmpPortfolio = portfolio_p->curPortfolio;
	//Pekar p� noden f�r f�rsta aktien i portf�ljens f�rsta datum
	Portfolio::portfolionode::stockinfo *tmpStock = tmpPortfolio->curStock;
	//Pekar p� noden f�r f�rsta datumet i mitt index (OMX30)
	Stock::node *index = omxS30_p->firstStockDate;

	while(tmpPortfolio != NULL){
		//nu borde jag uppdatera v�rdet f�r alla parametrar:
		// 1: datumet
		// 2: v�rdet p� portf�ljen
		// 3: antalet aktier?
		//cout << "tmpPortfolio: " <<  tmpPortfolio->date << endl;
		cout << "INDEX: " <<  index->date << endl;

		if (index->bearBull == 1800){
			cout << "BULL Handla!" << endl;
			//handla s� m�nga aktier du har r�d att handla den dagen
		} else {
			cout << "BEAR Handla inte!" << endl;
			//cout << portfolio_p->portfolioMoney << endl;
			//portfolio_p->buy2(omxS30_p ,portfolio_p->portfolioMoney, index->date);
			portfolio_p->buy3(index,omxS30_p->name,portfolio_p->portfolioMoney, tmpPortfolio);

		}
		tmpStock = tmpPortfolio->curStock;
		tmpPortfolio=tmpPortfolio->next;
		index=index->next;
	}

	///ONLY FOR PRINTING
	tmpPortfolio=portfolio_p->curPortfolio;
	tmpStock = tmpPortfolio->curStock;
	
	while(tmpPortfolio != NULL){
		cout << "tmpPortfolio: " <<  tmpPortfolio->date << endl;

		while(tmpStock != NULL){
			cout << "tmpStock: " <<  tmpStock->name << endl;
			tmpStock = tmpStock->next;
		}
		tmpPortfolio=tmpPortfolio->next;
	}
	/*while(index != NULL){

		//Uppdatera aktiev�rdet fr�n f�reg�ende varv:
		tmpPortfolio->totalValue =
			tmpStock->stockValue * tmpStock->nrOfStocks + portfolio_p->portfolioMoney;


		cout << "Portfolio->TotalValue: " << tmpPortfolio->totalValue << endl;
		cout << "Portfolio->stockValue: " << tmpStock->stockValue << endl;
		cout << "portfolio_p->portfolioMoney: " << portfolio_p->portfolioMoney << endl;
		

////////////////////////
		tmpPortfolio->totalValue = portfolio_p->portfolioValue(portfolio_p, stock->date);
		stock=stock->next;
		tmpPortfolio->date = stock->date;
/////////////////////
		//cout << "sven date: " << tmpPortfolio->date << endl;

	}
*/
}

Algorithms::~Algorithms() {
	// TODO Auto-generated destructor stub
}
