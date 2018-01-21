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

			while (money >= stockValue)
				{
					//dra av värdet i portföljen för varje aktie jag köper
					money = money - stockValue;
					cash = cash - stockValue;
					++nrOfStocks;
					cout << "money = " << money << endl;
					cout << "stocknode->close = " << stockValue << endl;
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
		while (portnode->curStock->nrOfStocks > 0)
		{
			cash = cash + stocknode->close;
			portnode->curStock->nrOfStocks = portnode->curStock->nrOfStocks - 1;
		}
	}
}

int Portfolio::NrOfStocksInPortfolio(Portfolio::portfolionode* curPortfolioDay,
			   						 string stock)
{
	

	while (curPortfolioDay->curStock != NULL)
	{
		string stockName = curPortfolioDay->curStock->name;
		cout << " stockName = " << stockName << endl;
		if (stock == stockName)
		{
			cout << "test otur!!" << endl;
			return curPortfolioDay->curStock->nrOfStocks;
			
		}

		curPortfolioDay->curStock = curPortfolioDay->curStock->next;
	}
	return 0;
}

int Portfolio::stockValue(Portfolio::portfolionode* curPortfolioDay,
			   Stock stocks[])
{
	int stockValue = 0;

	
	for (int i = 0; i < NROFSTOCKS; ++i)
	{
		int nrOfStocks = 0;
		Stock::dayInfo *curStocks = stocks[i].head;
		
		nrOfStocks = NrOfStocksInPortfolio(curPortfolioDay, stocks[i].name);
		
		if (nrOfStocks != 0 )
		{
			cout << "nrOfStocks !!" << nrOfStocks << endl;
		}
		stockValue = stockValue + nrOfStocks*curStocks->close;
	}

	return stockValue;
}

void Portfolio::updateBeginningOfDay2(Portfolio::portfolionode* portfolioNode,
									  Stock stocks[])
{	
	//vad vill jag göra i update?
	/*
	1: Lägga till allt som jag gjorde under gårdagen,
	dvs: hade jag 3 A-aktier  inför igår och köpte två till
	då ska jag lägga till så jag har 5 A-aktier nästa dag
	*/
	//cout << " portfolioNode->curStock wtf" << portfolioNode->curStock <<  endl; 
	
	Portfolio::portfolionode::stockinfo portfoloioNode;
	portfoloioNode = portfolioNode->myStockinfo;
	

	cout << " stockName = " << portfoloioNode.name << endl;
	cout << " nrOfStocks = " << portfoloioNode.nrOfStocks << endl;

	if (portfolioNode->curStock != NULL)
	{
		cout << " portfolioNode OMGOM" << endl;
	
		int totalStockValue = 0;
		totalStockValue = stockValue(portfolioNode, stocks);
		//cout << "totalStockValue = " << totalStockValue << endl;
		portfolioNode->portfolioValue = cash + totalStockValue;

	//Uppdatera mitt gamla portföljvärde

/*
	for (int i = 0; i < NROFSTOCKS; ++i)
	{
		Stock::dayInfo *curStock = stocks[i].head;
	}*/

	}
	portfolioNode=portfolioNode->next;

 //cout << "updateBeginningOfDay2" << endl;
 
}


void Portfolio::updateBeginningOfDay(Portfolio::portfolionode *pPortF, 
									 Portfolio::portfolionode *cPortF,
									 Stock::dayInfo *pStock,
									 Stock::dayInfo *cStock)
{	
	
	if (pPortF->curStock != NULL)
	{	
		cPortF->portfolioValue =  pPortF->portfolioValue;
		while (pPortF->curStock != NULL) 
		{
			Portfolio::portfolionode::stockinfo *tmpnode = 
				new Portfolio::portfolionode::stockinfo;

			tmpnode->name = pPortF->curStock->name;
			tmpnode->nrOfStocks = pPortF->curStock->nrOfStocks;


			//Räknar ut nästa värde på portföljen
			cPortF->portfolioValue = cPortF->portfolioValue + 
				(tmpnode->nrOfStocks)*((cStock->close)-(pStock->close));
		    
		    tmpnode->next=cPortF->curStock;
		    cPortF->curStock=tmpnode;
		    pPortF->curStock = pPortF->curStock->next;
		}
	}
	else {
		cPortF->portfolioValue =  pPortF->portfolioValue;
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

