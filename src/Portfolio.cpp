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



void Portfolio::add_to_bank(float value, string date)
{
	/*portfolionode_p portfolio_p = curPortfolio;
	portfolionode::stockinfo *tmpnode = portfolio_p->curStock;

	while(portfolio_p != NULL){
		if (portfolio_p->date >= date){
			tmpnode=portfolio_p->curStock;
			while (tmpnode != NULL){
				portfolionode::stockinfo *portfolio = tmpnode;

				while (portfolio->name!="portfolio value"){
					portfolio=portfolio->next;
				}

				if (tmpnode->name=="bank"){
					tmpnode->stockValue = tmpnode->stockValue+value;
					portfolio->stockValue= portfolio->stockValue + value;
				}

				tmpnode=tmpnode->next;
			}
		}
		tmpnode=portfolio_p->curStock;
		portfolio_p=portfolio_p->next;
	}*/
}



void Portfolio::remove_from_bank(float stockValue,string date)
{
	/*portfolionode_p tmp = curPortfolio;
	portfolionode::stockinfo *tmpnode = tmp->curStock;

	while((tmp!= NULL)){
		if (tmp->date >= date){
			tmpnode=tmp->curStock;
			while (tmpnode != NULL){
				portfolionode::stockinfo *portfolio = tmpnode;
				while (portfolio->name!="portfolio value"){
					portfolio=portfolio->next;
				}
				if (tmpnode->name=="bank"){
					tmpnode->stockValue = tmpnode->stockValue-stockValue;
					portfolio->stockValue= portfolio->stockValue - stockValue;
				}
				tmpnode=tmpnode->next;
				}
			}
		tmpnode=tmp->curStock;
		tmp=tmp->next;
	}*/
}


void Portfolio::buy2(Stock *stock, float money, string date)
{/*
	int nrOfStocks = 0;
	Stock::node *tmpStock = stock->firstStockDate;
	//Kolla att stocken inte finns i portföljen -> lägg till en ny!
	if (stockInPortfolio(stock->name) == false)
	{	
		while (money >= tmpStock->close)
		{
			//dra av värdet i portföljen för varje aktie jag köper
			portfolioMoney = portfolioMoney - tmpStock->close;
			money = money - tmpStock->close;
			++nrOfStocks;
		}

		portfolionode *tmpPortfolio_p = curPortfolio;
		portfolionode::stockinfo *tmpnode = tmpPortfolio_p->curStock;

		//Skapa en ny aktie i portföljen

		tmpnode = new portfolionode::stockinfo;
		tmpnode->name = stock->name;
		tmpnode->nrOfStocks = nrOfStocks;
		tmpnode->stockValue = tmpStock->close;

		//Sätt portföljen att peka på noden jag precis fyllde på med data
	    tmpPortfolio_p->curStock=tmpnode;//->next;
		cout << "tmpnode->name " << tmpnode->name << endl;
		cout << "nr of stocks: " << tmpnode->nrOfStocks << endl;
		cout << "DATUM::::" << tmpPortfolio_p->date << endl;
	    //tmpnode=NULL;

	}*/
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

void Portfolio::buy3(Stock::node *stocknode, string stockname, float money, Portfolio::portfolionode *portnode, Portfolio *port)
{
	int nrOfStocks = 0;
	if (money <= port->cash) {
	//Kolla att stocken inte finns i portföljen -> lägg till en ny!
	if (stockInPortfolio(stockname,portnode->curStock) == false)
	{	
		cout << "--------------- aktie saknas: skapa nytt element --------------------" << endl;
		while (money >= stocknode->close)
			{
				//dra av värdet i portföljen för varje aktie jag köper
				money = money - stocknode->close;
				port->cash = port->cash - stocknode->close;
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
		cout << "--------------- aktie finns: lägg till i existerande --------------------" << endl;
	}
}
}

void Portfolio::updateBeginningOfDay(Portfolio::portfolionode *previousPort,Portfolio::portfolionode *currentPort,Stock::node *previousStock,Stock::node *currentStock)
{	
	Portfolio::portfolionode::stockinfo *previousDay = previousPort->curStock;
	Portfolio::portfolionode::stockinfo *currentDay = currentPort->curStock;

	if (previousDay != NULL)
	{	
		Portfolio::portfolionode::stockinfo *tmpnode = new Portfolio::portfolionode::stockinfo;
		tmpnode->name = previousDay->name;
		tmpnode->nrOfStocks = previousDay->nrOfStocks;
		cout << "diff: " << ((currentStock->close)-(previousStock->close)) << endl;
		cout << "previous current: " << previousStock->close << endl;
		cout << "close current: " << currentStock->close << endl;
		currentPort->portfolioValue =  previousPort->portfolioValue + (tmpnode->nrOfStocks)*((currentStock->close)-(previousStock->close));
	    tmpnode->next=currentPort->curStock;
	    currentPort->curStock=tmpnode;
	    previousDay = previousDay->next;

	}
	else{currentPort->portfolioValue =  previousPort->portfolioValue;}
	

}

float Portfolio::portfolioValue(Portfolio* portfolio, string date)
{
	/*//string stockName = portfolio->myPortfolionode.myStockinfo.name;
	portfolionode_p tmpNode = portfolio->curPortfolio;

	Portfolio::portfolionode::stockinfo *stock = tmpNode->curStock;
	tmpNode->portfolioValue = cash;

	//cout << "stockName = " << stockName << endl;
	//cout << "portfolio->portfolionode::date = " << portfolio->portfolionode::date << endl;
	Stock tmpStock;
	while(stock != NULL)
	{
		string stockName = stock->name;
		//tmpNode->totalValue = tmpNode->totalValue + tmpStock.stockValue(stockName, date);
		cout << " tmpNode->portfolioValue = " << tmpNode->portfolioValue << endl;
		stock = stock->next;
	}*/
	/*	string stockName = portfolio->portfolionode::stockinfo::name;
		//stockinfo =

		portfolio->portfolionode::totalValue =
				portfolio->portfolionode::totalValue + Stock::stockValue(stockName, date);

	}*/


	return 1.337;
}

void Portfolio::buy(Stock stock, float volume, string date)
{
/*
	portfolionode *tmp = curPortfolio;
	portfolionode::stockinfo *tmpnode = tmp->curStock;
	Stock::node *stocktmp = stock.firstStockDate;
	int bankupdated = 0;

	while((tmp!= NULL) && (stocktmp != NULL)){
		if (tmp->date >= date){
			while (tmp->date > stocktmp->date){
				stocktmp=stocktmp->next;
			}

			if (stocktmp->date == tmp->date){
				tmpnode=tmp->curStock;
				portfolionode::stockinfo *portfolio = tmpnode;


				int stockexist = 0;
				while (tmpnode != NULL){
					if (tmpnode->name == "portfolio value"){

						portfolio=tmpnode;
					}

					tmpnode=tmpnode->next;
				}
				tmpnode=tmp->curStock;

				//Check if the stock exist. If it exist it will be updated. 
				//If it does not exist it will be added.
				while (tmpnode != NULL){
					if (tmpnode->name==stock.name){
						//The stock exist. updating node"
						tmpnode->stockValue = tmpnode->stockValue+volume;
						if (bankupdated == 0){
							remove_from_bank((stocktmp->close)*volume,tmp->date);
							bankupdated=1;
							cout << "REMOVED FROM BANK" << endl;
						} 
						portfolio->stockValue= portfolio->stockValue + (stocktmp->close)*volume;
						stockexist=1;
						break;
					} 

					tmpnode=tmpnode->next;

					if ((tmpnode == NULL) && (stockexist==0)){
					   //The stock does not exist. creating new node"
					   tmpnode = new portfolionode::stockinfo;
					   tmpnode->name = stock.name;
					   tmpnode->stockValue = volume;

						if (bankupdated == 0){
							remove_from_bank((stocktmp->close)*volume,tmp->date);
							bankupdated=1;
							cout << "REMOVED FROM BANK" << endl;
						}
					   portfolio->stockValue = portfolio->stockValue + (stocktmp->close)*volume;
         			   tmpnode->next=tmp->curStock;
					   tmp->curStock=tmpnode;
   					   tmpnode=NULL;

					}
				}
			}
		}
		tmpnode=tmp->curStock;
		tmp=tmp->next;
	}*/
}

void Portfolio::sell(Stock stock,float volume,string date)
{

	/*portfolionode_p tmp = curPortfolio;
	portfolionode::stockinfo *tmpnode = tmp->curStock;
	Stock::node *stocktmp = stock.firstStockDate;
	int bankupdated = 0;

	while((tmp!= NULL) && (stocktmp != NULL)){
		if (tmp->date >= date){
			while (tmp->date > stocktmp->date){
				stocktmp=stocktmp->next;
			}

			if (stocktmp->date == tmp->date){
				tmpnode=tmp->curStock;
				portfolionode::stockinfo *portfolio = tmpnode;
				portfolionode::stockinfo *bank = tmpnode;

				int stockexist = 0;
				while (tmpnode != NULL){
					if (tmpnode->name == "portfolio value"){
						portfolio = tmpnode;
					}

					if (tmpnode->name == "bank"){
						bank = tmpnode;
					}
					tmpnode=tmpnode->next;
				}
				tmpnode=tmp->curStock;

				//Check if the stock exist. If it exist it will be updated.
				//If it does not exist it will be added.
				while (tmpnode != NULL){
					if (tmpnode->name==stock.name){
						//The stock exist. updating node"
						tmpnode->stockValue = tmpnode->stockValue-volume;
						if (bankupdated == 0){
							add_to_bank((stocktmp->close)*volume,tmp->date);
							bankupdated=1;
							cout << "ADDED TO BANK" << endl;
						}
						portfolio->stockValue= portfolio->stockValue - (stocktmp->close)*volume;
						stockexist=1;
						break;
					}

					tmpnode=tmpnode->next;

					if ((tmpnode == NULL) && (stockexist==0)){
						cout << "The stock does not exist" <<endl;
					 }
				}
			}
		}
		tmpnode=tmp->curStock;
		tmp=tmp->next;
	}*/
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

