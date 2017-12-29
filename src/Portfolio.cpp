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
	Stock::node *stocktmp = portf_time.firstStockDate;

	while(stocktmp!= NULL){
		add_date(stocktmp->date);
		Portfolio::portfoliolength++;
		stocktmp=stocktmp->next;
	}
}

void Portfolio::add_date(string date)
{
	portfolionode_p tmp = new portfolionode;
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

bool Portfolio::stockInPortfolio(string stockname,Portfolio::portfolionode::stockinfo *portnode)
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

void Portfolio::buy(Stock::node *stocknode, string stockname, float money, Portfolio::portfolionode *portnode)
{
	int nrOfStocks = 0;
	if (money <= cash) {
		//Kolla att stocken inte finns i portföljen -> lägg till en ny!
		if (stockInPortfolio(stockname,portnode->curStock) == false)
		{	
			while (money >= stocknode->close)
				{
					//dra av värdet i portföljen för varje aktie jag köper
					money = money - stocknode->close;
					cash = cash - stocknode->close;
					++nrOfStocks;
				}
			//Skapa en ny aktie i portföljen
			Portfolio::portfolionode::stockinfo *tmpnode = new Portfolio::portfolionode::stockinfo;
			
			tmpnode->name = stockname;
			tmpnode->nrOfStocks = nrOfStocks;
		    tmpnode->next=portnode->curStock;
		    portnode->curStock=tmpnode;
		}
		else {
			while (money >= stocknode->close)
				{
					//dra av värdet i portföljen för varje aktie jag köper
					money = money - stocknode->close;
					cash = cash - stocknode->close;
					++nrOfStocks;
				}
			portnode->curStock->nrOfStocks = portnode->curStock->nrOfStocks + nrOfStocks;
		}
	}
}

void Portfolio::sell(Stock::node *stocknode, string stockname, int percentageOfStocks, Portfolio::portfolionode *portnode)
{
	if (stockInPortfolio(stockname,portnode->curStock) == true)
	{
		while (portnode->curStock->nrOfStocks > 0)
		{
			cash = cash + stocknode->close;
			portnode->curStock->nrOfStocks = portnode->curStock->nrOfStocks - 1;
		}
	}
}

void Portfolio::updateBeginningOfDay(Portfolio::portfolionode *previousPort,Portfolio::portfolionode *currentPort,Stock::node *previousStock,Stock::node *currentStock)
{	
	Portfolio::portfolionode::stockinfo *previousDay = previousPort->curStock;
	Portfolio::portfolionode::stockinfo *currentDay = currentPort->curStock;

	if (previousDay != NULL)
	{	
		currentPort->portfolioValue =  previousPort->portfolioValue;
		while (previousDay != NULL) 
		{
			Portfolio::portfolionode::stockinfo *tmpnode = new Portfolio::portfolionode::stockinfo;
			tmpnode->name = previousDay->name;
			tmpnode->nrOfStocks = previousDay->nrOfStocks;
			currentPort->portfolioValue = currentPort->portfolioValue + (tmpnode->nrOfStocks)*((currentStock->close)-(previousStock->close));
		    tmpnode->next=currentPort->curStock;
		    currentPort->curStock=tmpnode;
		    previousDay = previousDay->next;
		}
	}
	else{
		currentPort->portfolioValue =  previousPort->portfolioValue;
	}
}

void Portfolio::Print()
{
	/*cout << "PRINT: " << endl;
	portfolionode_p tmp = curPortfolio;
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

