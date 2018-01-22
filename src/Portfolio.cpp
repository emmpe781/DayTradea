/*
 * Portfolio.cpp
 *
 *  Created on: 15 aug. 2017
 *      Author: Otur1337
 */
#define _USE_MATH_DEFINES
#include "Portfolio.h"
#include "Readfile.h"
#include "Stock.h"
#include <cmath>

using namespace std;

Portfolio::Portfolio(string date) {
	Stock portf_time;
	string fname_time="../data/stockdata_Portfolio_use.dat";
	ReadFile rf;
	rf.Read(fname_time, &portf_time, date);
	Portfolio::portfoliolength = 0;
	Portfolio::cash = 0;
	Stock::dayInfo *stocktmp = portf_time.head;

	while(stocktmp!= NULL){
		add_date(stocktmp->date);
		Portfolio::portfoliolength++;
		stocktmp=stocktmp->next;
	}
}

void Portfolio::add_date(string date)
{
	portfolionode *tmp = new portfolionode;
	tmp->date = date;
	tmp->portfolioValue = 0;
	
	tmp->next = NULL; //TODO: Kontrollera vad som faktiskt sker nedan

	if(curPortfolio == NULL)
	{	
		curPortfolio = tmp;
		tail = tmp;
	}
	else
	{
		tail->next = tmp;
		tail = tail->next;
	}
}

void Portfolio::setStartValue(float startValue)
{
	cash = startValue;
	cout << cash << " = cash" << endl;
}

bool Portfolio::stockInPortfolio(string stockname,
	 							 Portfolio::portfolionode::stockinfo *portnode)
{
	while (portnode != NULL)
	{	
		if (stockname == portnode->name)
		{
			return true;
		}
		portnode = portnode->next;
	}
	return false;
}

void Portfolio::buy(float stockValue, 
					string stockname, 
					float money, 
					Portfolio::portfolionode *portnode)
{
	int nrOfStocks = 0;
	if (money <= cash) {
		//Kolla att stocken inte finns i portföljen -> lägg till en ny!
		if (stockInPortfolio(stockname,portnode->curStock) == false)
		{	

			while ((money >= stockValue) && (stockValue > 0))
				{
					//dra av värdet i portföljen för varje aktie jag köper
					money = money - stockValue;
					cash = cash - stockValue;
					++nrOfStocks;
				}
			//Skapa en ny aktie i portföljen
			Portfolio::portfolionode::stockinfo *tmpnode = 
				new Portfolio::portfolionode::stockinfo;
			
			tmpnode->name = stockname;
			tmpnode->nrOfStocks = nrOfStocks;
		    tmpnode->next=portnode->curStock;
		    portnode->curStock=tmpnode;
		}

		
		else {
			
			while ((money >= stockValue) && (stockValue > 0))
			{
				//dra av värdet i portföljen för varje aktie jag köper
				money = money - stockValue;
				cash = cash - stockValue;
				++nrOfStocks;
			}
			portnode->curStock->nrOfStocks =
				portnode->curStock->nrOfStocks + nrOfStocks;
		} /*else*/
	}
}

void Portfolio::sell(Stock::dayInfo *stocknode,  
					 string stockname, 
					 int percentageOfStocks,  
					 Portfolio::portfolionode *portnode)
{
	if (stockInPortfolio(stockname,portnode->curStock) == true)
	{
		Portfolio::portfolionode::stockinfo *tmp = portnode->curStock;
		while (tmp != NULL)
		{	
			if (stockname == tmp->name)
			{
				while (tmp->nrOfStocks > 0)
				{
					cash = cash + stocknode->close;
					tmp->nrOfStocks = tmp->nrOfStocks - 1;
				}
			}
			tmp = tmp->next;
		}
		tmp = portnode->curStock;
	}	
}


int Portfolio::NrOfStocksInPortfolio(Portfolio::portfolionode* curPortfolioDay,
			   						 string stock)
{
	string stockName = curPortfolioDay->curStock->name;

	//We have found our stock in portfolio
	if (stock == stockName)
	{
		return curPortfolioDay->curStock->nrOfStocks;		
	}

	return 0;
}

int Portfolio::stockValue(Portfolio::portfolionode* curPortfolioDay,
			   			  Stock stocks[])
{

	for (int i = 0; i < NROFSTOCKS; ++i)
	{
		int nrOfStocks = 0;
		Stock::dayInfo *curStocks = stocks[i].head;
		

		nrOfStocks = NrOfStocksInPortfolio(curPortfolioDay, stocks[i].name);
		
		//We have found our stock in portfolio
		if (nrOfStocks != 0)
		{
			return nrOfStocks*curStocks->close;
		}
		
	}

	//This should never happend! This means the stock 
	//does not exist in stockclass, only in portfolio!
	return 0;
}

void Portfolio::updateBeginningOfDay2(Portfolio::portfolionode *portfolionode,
									  Stock stocks[])
{	
 
}


void Portfolio::updateBeginningOfDay(Portfolio::portfolionode *pPortF, 
									 Portfolio::portfolionode *cPortF,
									 Stock stocks[])
{	
	//The value of the portfolio before 
	//all stocks values are added
	cPortF->portfolioValue = cash;

	if (pPortF->curStock != NULL)
	{	

		while (pPortF->curStock != NULL) 
		{
			//The total value of all stocks of a specific type
			int value = 0;

			portfolionode::stockinfo *tmpnode = new portfolionode::stockinfo;

			tmpnode->name = pPortF->curStock->name;
			tmpnode->nrOfStocks = pPortF->curStock->nrOfStocks;

			//Value of one type of stocks in portfolio
			value = stockValue(pPortF, stocks);
			cPortF->portfolioValue = cPortF->portfolioValue + value;

			tmpnode->next = NULL;

			if(cPortF->curStock == NULL)
			{	
				cPortF->curStock = tmpnode;
				cPortF->tail = tmpnode;
			}
			else
			{
				cPortF->tail->next = tmpnode;
				cPortF->tail = cPortF->tail->next;
			}
			pPortF->curStock = pPortF->curStock->next;
		}
	}
	
	else 
	{
		cPortF->portfolioValue =  pPortF->portfolioValue;
	}
}

void Portfolio::Print()
{
	/*cout << "PRINT: " << endl;
	portfolionode tmp = curPortfolio;
	portfolionode::stockinfo *infotmp = tmp->curStock;
   	 

    while(tmp!= NULL){
    	cout << "--- date: " << tmp->date << endl;
		while(infotmp!=NULL){
			cout<< "name: " << infotmp->name;
			cout<< ", volume: " << infotmp->stockValue << endl;
			infotmp=infotmp->next;
		}
    	infotmp=tmp->curStock;
		tmp=tmp->next;
   }*/
}


Portfolio::~Portfolio() {
}

