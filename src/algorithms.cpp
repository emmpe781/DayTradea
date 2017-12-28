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

	Portfolio::portfolionode *tmpPortfolioDay = portfolio_p->curPortfolio; 	//Pekar p� noden f�r mitt f�rsta datum i portf�ljen
	Portfolio::portfolionode *previousPortfolioDay = portfolio_p->curPortfolio; 
	Portfolio::portfolionode::stockinfo *tmpStock = tmpPortfolioDay->curStock; //Pekar p� noden f�r f�rsta aktien i portf�ljens f�rsta datum
	Stock::node *index = omxS30_p->firstStockDate; 							//Pekar p� noden f�r f�rsta datumet i mitt index (OMX30)
	Stock::node *previousIndex = omxS30_p->firstStockDate;

	int i = 0;
	tmpPortfolioDay->portfolioValue = portfolio_p->cash;;
	while(tmpPortfolioDay != NULL){
		cout << "UPDAATE: " << endl;
		portfolio_p->updateBeginningOfDay(previousPortfolioDay,tmpPortfolioDay,previousIndex,index);
		
		if (index->bearBull == 1800){
			cout << "BULL Handla!" << endl;
			float moneyToBuyWith = portfolio_p->cash;
			portfolio_p->buy(index,omxS30_p->name,moneyToBuyWith, tmpPortfolioDay, portfolio_p);
			//handla s� m�nga aktier du har r�d att handla den dagen
		} 
		else { 
			cout << "BEAR Handla inte!" << endl;
			if(tmpPortfolioDay->curStock != NULL)
			{
				tmpStock = tmpPortfolioDay->curStock;
				int numberofstock = tmpStock->nrOfStocks;
				portfolio_p->sell(index,omxS30_p->name,numberofstock, tmpPortfolioDay, portfolio_p);
			}
		}

		cout << "--------------- PRINTING START --------------------" << endl;
		tmpStock = tmpPortfolioDay->curStock;

		cout << "Cash: " <<  portfolio_p->cash << endl;
		cout << "Date: " <<  tmpPortfolioDay->date << endl;
		cout << "PortfolioValue: " <<  tmpPortfolioDay->portfolioValue << endl;
		while(tmpStock != NULL){
			cout << "  StockName: " <<  tmpStock->name << endl;
			cout << "  NrOfStocks: " <<  tmpStock->nrOfStocks << endl;
			cout << "  --  " << endl;

			tmpStock = tmpStock->next;
		}
		cout << "--------------- PRINTING END --------------------" << endl;

		previousPortfolioDay=tmpPortfolioDay;
		previousIndex=index;
		tmpStock = tmpPortfolioDay->curStock;
		tmpPortfolioDay=tmpPortfolioDay->next;
		index=index->next;
		i=i+1;
	}
}


Algorithms::~Algorithms() {
	// TODO Auto-generated destructor stub
}

	///ONLY FOR PRINTING
	/*tmpPortfolio=portfolio_p->curPortfolio;
	tmpStock = tmpPortfolio->curStock;
	i=0;
	cout << "Cash: " <<  portfolio_p->cash << endl;

	cout << "--------------- PRINTING --------------------" << endl;
	while(i<5){
		cout << "------" << endl;

	//while(tmpPortfolio != NULL){
		cout << "Date: " <<  tmpPortfolio->date << endl;
		cout << "PortfolioValue: " <<  tmpPortfolio->portfolioValue << endl;

		while(tmpStock != NULL){
			cout << "  StockName: " <<  tmpStock->name << endl;
			cout << "  NrOfStocks: " <<  tmpStock->nrOfStocks << endl;
			cout << "  --  " << endl;

			tmpStock = tmpStock->next;
		}
		tmpStock = tmpPortfolio->curStock;
		tmpPortfolio=tmpPortfolio->next;
		i=i+1;
	}*/

