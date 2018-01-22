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
#include "math.h"
using namespace std;
const Stock::dayInfo * lastStockDate = NULL;


Algorithms::Algorithms() {
	// TODO Auto-generated constructor stub
	TimeToRecalibrate = true;
}

void Algorithms::updateStockDate(Stock stocks[])
{
	for (int i = 0; i < NROFSTOCKS; ++i)
	{
		Stock::dayInfo *curStocks = stocks[i].head;
		curStocks = curStocks->next;
		stocks[i].head = curStocks;
	}
}

void Algorithms::Algo(	string algo, 
						Portfolio *portfolio_p, 
						Stock stocks[]) {

    
	Portfolio::portfolionode *curPortfolioDay = 
		portfolio_p->curPortfolio;

	Portfolio::portfolionode *previousPortfolioDay = 
		portfolio_p->curPortfolio; 


	//Borde vilja flytta in allt stockrelaterat till algoritmerna?!
	//Endast ha kvar hur portföljen uppdateras här ute?!
	Stock::dayInfo *curStocks = stocks[0].head;
	Stock::dayInfo *previousStocks = stocks[0].head;

	curPortfolioDay->portfolioValue = portfolio_p->cash;

	while(curPortfolioDay != NULL){

		//Borde inte vilja skicka med previous och curPortfolioDay 
		//utan endast curDay, eftersom portfolioklassen själv 
		//borde ha kolla på gårdagens data.

		//Även cur och Previous stocks borde ägas portfolioklassen
		//Dvs, vi har en setfunktion i respektive algoritm som sätter 
		//antal aktier direkt i portföljen som den sedan kan styra över.
		
		portfolio_p->updateBeginningOfDay(previousPortfolioDay,
			 							  curPortfolioDay, 
			 							  stocks);
			

		///PRINTING	 /////////////////////////////////////////////////////////////
		Portfolio::portfolionode *tmp = curPortfolioDay;
		Portfolio::portfolionode::stockinfo *infotmp = tmp->curStock;

	    cout << "--- date: " << tmp->date << endl;
		while(infotmp!=NULL){
			cout<< "name: " << infotmp->name;
			cout<< ", volume: " << infotmp->nrOfStocks << endl;
			infotmp=infotmp->next;
		}

       	infotmp=tmp->curStock;
		///PRINTING	 /////////////////////////////////////////////////////////////


		//START - ALGO
		if (algo == "BEARBULL")
		{
			//Kommer behöva anpassas till den mer generiska designen
			//Algo_BearBull(portfolio_p, &stocks[0], curPortfolioDay, index);
		}
		if (algo == "CREATEINDEX")
		{
			//Skicka med aktier, portfölj, curPortfolioDay, 
			// curStocks kan jag ta fram i funktionen istället utifrån stocks.
			CreateIndex(portfolio_p, stocks);
		}
		//END - ALGO

		//curPortfolioDay=curPortfolioDay->next;

		
		//Borde ha en updatePortfolio här med!
		//portfolio_p->updateBeginningOfDay2(curPortfolioDay, stocks);

		updateStockDate(stocks);



		//Kommer ge att vi endast uppdaterar till nästa portföljdag
		//härifrån.

		previousPortfolioDay=curPortfolioDay;
		//previousStocks=curStocks;
		curPortfolioDay=curPortfolioDay->next;
		//curStocks=curStocks->next;
	}
}

void Algorithms::Algo_BearBull(Portfolio *portfolio_p, 
							   Stock *omxS30, 
							   Portfolio::portfolionode *tmpPortfolioDay,
							   Stock::dayInfo *index) {
	//Hur ska algen fungera?
	//1 loopa igenom alla datum i index
	//2 när index ligger i bull -> var 100 % investerad
	//3 när index ligger i bear -> var 0 & investerad
	float indexValue = index->close;

	if (index->bearBull == 1800){
		//cout << "BULL Handla!" << endl;
		float moneyToBuyWith = portfolio_p->cash;
		portfolio_p->buy(indexValue,omxS30->name,moneyToBuyWith, tmpPortfolioDay);
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
/*
int Algorithms::MaxNumberOfStocks(const float money, const float priceOfStock)
{
	float nrOfStocks = 0;
	nrOfStocks = money/priceOfStock; 
	return (int)floor(nrOfStocks);
}
*/


void Algorithms::RecalibratePortfolio(	Portfolio *portfolio_p, 
										Stock stocks[]) {

	float moneyToBuyWith = portfolio_p->cash; //+ money in stocks;
	int nrOfStocks = NROFSTOCKS; //NROFSTOCKS - "alla aktier som inte är aktiverade"

	float moneyForEachStock = moneyToBuyWith/nrOfStocks;

	cout << "Buy the following stocks after RecalibratePortfolio: " << endl << endl;
	//int nrOfActiveStocks = 0;
	for(int i = 0; i < NROFSTOCKS; ++i)
	{
		Stock::dayInfo *curStock = stocks[i].head;
		string stockName = stocks[i].name;
		float stockValue = curStock->close;


		if (!(curStock->exist))
		{
			continue;
		}

		Portfolio::portfolionode *curPortfolioDay = 
			portfolio_p->curPortfolio;

		//Printing the amount of each stock
		cout << "                                " << stockName 
			 << " = " << floor(moneyForEachStock/stockValue) << endl;

		portfolio_p->buy(stockValue, stockName, 
						 moneyForEachStock, curPortfolioDay);

		//JUST TO TEST
		portfolio_p->sell(curStock, stockName, 
						 1, curPortfolioDay);	

	}
	cout << endl << endl << endl; 
	TimeToRecalibrate = false;
}


void Algorithms::CreateIndex(Portfolio *portfolio_p, Stock stocks[]) 
{
	//Kommer behöva skapa en recalibratePortfolio() som ändrar index
	//om en ny aktie tillkommer.
	if(TimeToRecalibrate)
	{
		cout << "handla aktier " << endl;
		RecalibratePortfolio(portfolio_p, stocks);
	}

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

	




void Algorithms::SlayIndex(Portfolio *portfolio_p, Stock* omxS30_p) {

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