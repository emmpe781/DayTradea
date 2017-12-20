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
	//2 när index ligger i bull -> var 100 % investerad
	//3 när index ligger i bear -> var 0 & investerad

	Portfolio::portfolionode *tmpPortfolio = portfolio_p->curPortfolio; 	//Pekar på noden för mitt första datum i portföljen
	Portfolio::portfolionode::stockinfo *tmpStock = tmpPortfolio->curStock; //Pekar på noden för första aktien i portföljens första datum
	Stock::node *index = omxS30_p->firstStockDate; 							//Pekar på noden för första datumet i mitt index (OMX30)
	float PreviousPortfolioValue = portfolio_p->cash; //TEMPORARY

	int i = 0;
	while(i<5) {
	//portfolio_p->updateBeginningOfDay()
	tmpPortfolio->portfolioValue = PreviousPortfolioValue;

	//while(tmpPortfolio != NULL){
		if (index->bearBull == 1800){
			//cout << "BULL Handla!" << endl;
			//handla så många aktier du har råd att handla den dagen
		} 
		else { 
		if (i == 2) {
			//cout << "BEAR Handla inte!" << endl;
			float moneyToBuyWith = 5000;
			portfolio_p->buy3(index,omxS30_p->name,moneyToBuyWith, tmpPortfolio, portfolio_p);
		}
		}

		cout << "--------------- PRINTING --------------------" << endl;
		tmpStock = tmpPortfolio->curStock;

		cout << "Cash: " <<  portfolio_p->cash << endl;
		cout << "Date: " <<  tmpPortfolio->date << endl;
		cout << "PortfolioValue: " <<  tmpPortfolio->portfolioValue << endl;
		while(tmpStock != NULL){
			cout << "  StockName: " <<  tmpStock->name << endl;
			cout << "  NrOfStocks: " <<  tmpStock->nrOfStocks << endl;
			cout << "  --  " << endl;

			tmpStock = tmpStock->next;
		}

		//portfolio_p->updateEndOfDay()
		tmpStock = tmpPortfolio->curStock;
		tmpPortfolio=tmpPortfolio->next;
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

