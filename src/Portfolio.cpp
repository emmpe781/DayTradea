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
	cout << "initiating Portfolio... " << endl;
	Stock portf_time;
	string fname_time="../data/stockdata_portfolio_1986-10-01_2017-10-18_fill.dat";
	ReadFile1 rf2;
	rf2.Read(fname_time,&portf_time,date);
	Portfolio::portfoliolength = 0;
	Stock::node *stocktmp = portf_time.head;

	while(stocktmp!= NULL){
		add_date(stocktmp->date,"bank");
		Portfolio::portfoliolength++;
		stocktmp=stocktmp->next;
	}
}


void Portfolio::add_date(string date,string name)
{
	portfolionode *tmp = new portfolionode;
	tmp->date = date;

	portfolionode::stockinfo *tmpnode = new portfolionode::stockinfo;

	tmpnode->name = "portfolio value";
	tmpnode->volume = 0;
    tmpnode->next=tmp->head;

    tmp->head=tmpnode;

    tmpnode=new portfolionode::stockinfo;
	tmpnode->name = "bank";
	tmpnode->volume = 0;
    tmpnode->next=tmp->head;

    tmp->head=tmpnode;
	tmp->next = NULL;

	if(head == NULL)
	{
		head = tmp;
		tail = tmp;
	}
	else
	{
		tail->next = tmp;
		tail = tail->next;
	}
}


void Portfolio::add_to_bank(float volume,string date)
{
	portfolionode *tmp = head;
	portfolionode::stockinfo *tmpnode = tmp->head;

	while((tmp!= NULL)){
		if (tmp->date >= date){
			tmpnode=tmp->head;
			while (tmpnode != NULL){
				portfolionode::stockinfo *portfolio = tmpnode;

				while (portfolio->name!="portfolio value"){
					portfolio=portfolio->next;
				}
				if (tmpnode->name=="bank"){
					tmpnode->volume = tmpnode->volume+volume;
					portfolio->volume= portfolio->volume + volume;
				}
				tmpnode=tmpnode->next;
				}
			}
		tmpnode=tmp->head;
		tmp=tmp->next;
	}
}



void Portfolio::remove_from_bank(float volume,string date)
{
	portfolionode *tmp = head;
	portfolionode::stockinfo *tmpnode = tmp->head;

	while((tmp!= NULL)){
		if (tmp->date >= date){
			tmpnode=tmp->head;
			while (tmpnode != NULL){
				portfolionode::stockinfo *portfolio = tmpnode;
				while (portfolio->name!="portfolio value"){
					portfolio=portfolio->next;
				}
				if (tmpnode->name=="bank"){
					tmpnode->volume = tmpnode->volume-volume;
					portfolio->volume= portfolio->volume - volume;
				}
				tmpnode=tmpnode->next;
				}
			}
		tmpnode=tmp->head;
		tmp=tmp->next;
	}
}



void Portfolio::buy(Stock stock,float volume,string date)
{

	portfolionode *tmp = head;
	portfolionode::stockinfo *tmpnode = tmp->head;
	Stock::node *stocktmp = stock.head;
	int bankupdated = 0;

	while((tmp!= NULL) && (stocktmp != NULL)){
		if (tmp->date >= date){
			while (tmp->date > stocktmp->date){
				stocktmp=stocktmp->next;
			}

			if (stocktmp->date == tmp->date){
				tmpnode=tmp->head;
				portfolionode::stockinfo *portfolio = tmpnode;
				portfolionode::stockinfo *bank = tmpnode;

				int stockexist = 0;
				while (tmpnode != NULL){
					if (tmpnode->name == "portfolio value"){portfolio=tmpnode;}
					if (tmpnode->name == "bank"){bank=tmpnode;}
					tmpnode=tmpnode->next;
				}
				tmpnode=tmp->head;

				//Check if the stock exist. If it exist it will be updated. If it does not exist it will be added.
				while (tmpnode != NULL){
					if (tmpnode->name==stock.name){
						//The stock exist. updating node"
						tmpnode->volume = tmpnode->volume+volume;
						if (bankupdated == 0){
							remove_from_bank((stocktmp->close)*volume,tmp->date);
							bankupdated=1;
							cout << "REMOVED FROM BANK" << endl;
						}
						portfolio->volume= portfolio->volume + (stocktmp->close)*volume;
						stockexist=1;
						break;
					}

					tmpnode=tmpnode->next;

					if ((tmpnode == NULL) && (stockexist==0)){
					   //The stock does not exist. creating new node"
					   tmpnode = new portfolionode::stockinfo;
					   tmpnode->name = stock.name;
					   tmpnode->volume = volume;

						if (bankupdated == 0){
							remove_from_bank((stocktmp->close)*volume,tmp->date);
							bankupdated=1;
							cout << "REMOVED FROM BANK" << endl;
						}
					   portfolio->volume = portfolio->volume + (stocktmp->close)*volume;
         			   tmpnode->next=tmp->head;
					   tmp->head=tmpnode;
   					   tmpnode=NULL;

					 }
				}
			}
		}
		tmpnode=tmp->head;
		tmp=tmp->next;
	}
}

void Portfolio::sell(Stock stock,float volume,string date)
{

	portfolionode *tmp = head;
	portfolionode::stockinfo *tmpnode = tmp->head;
	Stock::node *stocktmp = stock.head;
	int bankupdated = 0;

	while((tmp!= NULL) && (stocktmp != NULL)){
		if (tmp->date >= date){
			while (tmp->date > stocktmp->date){
				stocktmp=stocktmp->next;
			}

			if (stocktmp->date == tmp->date){
				tmpnode=tmp->head;
				portfolionode::stockinfo *portfolio = tmpnode;
				portfolionode::stockinfo *bank = tmpnode;

				int stockexist = 0;
				while (tmpnode != NULL){
					if (tmpnode->name == "portfolio value"){portfolio=tmpnode;}
					if (tmpnode->name == "bank"){bank=tmpnode;}
					tmpnode=tmpnode->next;
				}
				tmpnode=tmp->head;

				//Check if the stock exist. If it exist it will be updated. If it does not exist it will be added.
				while (tmpnode != NULL){
					if (tmpnode->name==stock.name){
						//The stock exist. updating node"
						tmpnode->volume = tmpnode->volume-volume;
						if (bankupdated == 0){
							add_to_bank((stocktmp->close)*volume,tmp->date);
							bankupdated=1;
							cout << "ADDED TO BANK" << endl;
						}
						portfolio->volume= portfolio->volume - (stocktmp->close)*volume;
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
		tmpnode=tmp->head;
		tmp=tmp->next;
	}
}

void Portfolio::Print()
{
	cout << "PRINT: " << endl;
	portfolionode *tmp = head;
	portfolionode::stockinfo *infotmp = tmp->head;
   	 

    while(tmp!= NULL){
    	cout << "--- date: " << tmp->date << endl;
		while(infotmp!=NULL){
			cout<< "name: " << infotmp->name;
			cout<< ", volume: " << infotmp->volume << endl;
			infotmp=infotmp->next;
		}
    	infotmp=tmp->head;
		tmp=tmp->next;
   }
}


Portfolio::~Portfolio() {
}

