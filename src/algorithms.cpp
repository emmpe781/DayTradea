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
const Stock::dayInfo * lastStockDate = NULL;


Algorithms::Algorithms() {
	// TODO Auto-generated constructor stub

}



void Algorithms::Algo(string algo,Portfolio_p portfolio_p, Stock stocks[]) {
	Portfolio::portfolionode *tmpPortfolioDay = portfolio_p->curPortfolio;
	Portfolio::portfolionode *previousPortfolioDay = portfolio_p->curPortfolio; 
	Stock::dayInfo *index = stocks[0].head;
	Stock::dayInfo *previousIndex = stocks[0].head;

	int i = 0;
	tmpPortfolioDay->portfolioValue = portfolio_p->cash;
	while(tmpPortfolioDay != NULL){
		portfolio_p->updateBeginningOfDay(previousPortfolioDay,
			 							  tmpPortfolioDay, 
			 							  previousIndex, 
			 							  index);
		//START - ALGO
		if (algo == "BEARBULL")
		{
			Algo_BearBull(portfolio_p, &stocks[0], tmpPortfolioDay, index);
		}
		if (algo == "CREATEINDEX")
		{
			CreateIndex(portfolio_p,stocks);
		}
		//END - ALGO
		previousPortfolioDay=tmpPortfolioDay;
		previousIndex=index;
		tmpPortfolioDay=tmpPortfolioDay->next;
		index=index->next;
		i=i+1;
	}
}

void Algorithms::Algo_BearBull(Portfolio_p portfolio_p, Stock_p omxS30, 
							   Portfolio::portfolionode *tmpPortfolioDay,
							   Stock::dayInfo *index) {
	//Hur ska algen fungera?
	//1 loopa igenom alla datum i index
	//2 när index ligger i bull -> var 100 % investerad
	//3 när index ligger i bear -> var 0 & investerad

	if (index->bearBull == 1800){
		//cout << "BULL Handla!" << endl;
		float moneyToBuyWith = portfolio_p->cash;
		portfolio_p->buy(index,omxS30->name,moneyToBuyWith, tmpPortfolioDay);
		//handla så många aktier du har råd att handla den dagen
	} 
	else { 
		//cout << "BEAR Handla inte!" << endl;
		if(tmpPortfolioDay->curStock != NULL)
		{
			portfolio_p->sell(index,omxS30->name,1, tmpPortfolioDay);
		}
	}
}

void Algorithms::CreateIndex(Portfolio_p portfolio_p, Stock stocks[]){

	for(int i = 0; i < NROFSTOCKS; ++i)
	{
		cout << "stocks[i].name " << stocks[i].name << endl;
		
	}

	




	//DEL1 Skapa eget index
	//Ta in de 10 största investmentbolagen och äg lika stor del av varje
	//Bolagen:
	//Investor, Industrivärden, Svolder, Creades, Ratos, Östersund, Bure, Latour, Lundberg
	//Plotta ut resultatet


	//if (omx30 bulltrend)
		//while (stockInList != 0)
			//portfolio_p->buy(curStock, portfolioMoney/10)

	//else (omx30 beartrend)
		//while (stockInList != 0)
			//portfolio_p->sell(curStock)		

	


}

void Algorithms::SlayIndex(Portfolio_p portfolio_p, Stock_p omxS30_p) {

	//DEL2 Se om det går att slå mitt egenskapta index.
	//3 Loopa igenom alla aktier, välj ut de 4-8 bästa genom att välja bort de sämsta?
	//4 Hur ska de värderas? P.s.s som Bear/Bull? Behöver de få en värderingssiffra?
	// T.ex. positivt ma200 och ma50, ma50 > ma200
	// lutning på ma200 och ma50?

	//På sikt kanske det går att ta in nyckelvärden för respektive aktie och ta med i värdering.
	//Dvs. hur förändras pe-tal över tid i jämförelse med aktiekursen?

	
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