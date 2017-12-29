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

	Portfolio::portfolionode *tmpPortfolioDay = portfolio_p->curPortfolio; 	//Pekar på noden för mitt första datum i portföljen
	Portfolio::portfolionode *previousPortfolioDay = portfolio_p->curPortfolio; 
	Portfolio::portfolionode::stockinfo *tmpStock = tmpPortfolioDay->curStock; //Pekar på noden för första aktien i portföljens första datum
	Stock::node *index = omxS30_p->firstStockDate; 							//Pekar på noden för första datumet i mitt index (OMX30)
	Stock::node *previousIndex = omxS30_p->firstStockDate;

	int i = 0;
	tmpPortfolioDay->portfolioValue = portfolio_p->cash;;
	while(tmpPortfolioDay != NULL){
		portfolio_p->updateBeginningOfDay(previousPortfolioDay,tmpPortfolioDay,previousIndex,index);
		
		//START - ALGO
		if (index->bearBull == 1800){
			cout << "BULL Handla!" << endl;
			float moneyToBuyWith = portfolio_p->cash;
			portfolio_p->buy(index,omxS30_p->name,moneyToBuyWith, tmpPortfolioDay);
			//handla så många aktier du har råd att handla den dagen
		} 
		else { 
			cout << "BEAR Handla inte!" << endl;
			if(tmpPortfolioDay->curStock != NULL)
			{
				portfolio_p->sell(index,omxS30_p->name,1, tmpPortfolioDay);
			}
		}
		//END - ALGO

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


/*		cout << "--------------- PRINTING START --------------------" << endl;
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
*/