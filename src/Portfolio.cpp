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
	string fname_time="../data/stockdata_Portfolio_use.dat";
	ReadFile rf;
	rf.Read(fname_time,&portf_time,date);
	Portfolio::portfoliolength = 0;
	Stock::node *stocktmp = portf_time.head;

	while(stocktmp!= NULL){
		//if (stocktmp->date >= date){
			add_date(stocktmp->date,"bank");
			Portfolio::portfoliolength++;
		//}
		stocktmp=stocktmp->next;
	}
}



/*void Portfolio::insert_end(string date)
  {
	portfolionode *temp=new portfolionode;
    temp->date=date;
    temp->next=NULL;
    if(head==NULL)
    {
      head=temp;
      tail=temp;
      temp=NULL;
    }
    else
    {
      tail->next=temp;
      tail=temp;
    }
  }

void Portfolio::insert_start(string date)
{
	portfolionode *temp=new portfolionode;
    temp->date=date;
	temp->next=head;
	head=temp;
}
*/
void Portfolio::add_date(string date,string name)
{
	portfolionode *tmp = new portfolionode;
	tmp->date = date;

	portfolionode::stockinfo *tmpnode = new portfolionode::stockinfo;

	tmpnode->name = "portfolio value";
	tmpnode->volume = 0;
    tmpnode->next=tmp->curStock;

    tmp->curStock=tmpnode;

    tmpnode=new portfolionode::stockinfo;
	tmpnode->name = "bank";
	tmpnode->volume = 0;
    tmpnode->next=tmp->curStock;

    tmp->curStock=tmpnode;
	tmp->next = NULL;

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


void Portfolio::add_to_bank(float value, string date)
{
	portfolionode *tmp = curPortfolio;
	portfolionode::stockinfo *tmpnode = tmp->curStock;

	while(tmp != NULL){
		if (tmp->date >= date){
			tmpnode=tmp->curStock;
			while (tmpnode != NULL){
				portfolionode::stockinfo *portfolio = tmpnode;

				while (portfolio->name!="portfolio value"){
					portfolio=portfolio->next;
				}

				if (tmpnode->name=="bank"){
					tmpnode->volume = tmpnode->volume+value;
					portfolio->volume= portfolio->volume + value;
				}

				tmpnode=tmpnode->next;
			}
		}
		tmpnode=tmp->curStock;
		tmp=tmp->next;
	}
}



void Portfolio::remove_from_bank(float volume,string date)
{
	portfolionode *tmp = curPortfolio;
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
					tmpnode->volume = tmpnode->volume-volume;
					portfolio->volume= portfolio->volume - volume;
				}
				tmpnode=tmpnode->next;
				}
			}
		tmpnode=tmp->curStock;
		tmp=tmp->next;
	}
}



void Portfolio::buy(Stock stock, float volume, string date)
{

	portfolionode *tmp = curPortfolio;
	portfolionode::stockinfo *tmpnode = tmp->curStock;
	Stock::node *stocktmp = stock.head;
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
						tmpnode->volume = tmpnode->volume+volume;
						if (bankupdated == 0){
							remove_from_bank((stocktmp->close)*volume,tmp->date);
							bankupdated=1;
							cout << "REMOVED FROM BANK" << endl;
						} /*if*/
						portfolio->volume= portfolio->volume + (stocktmp->close)*volume;
						stockexist=1;
						break;
					} /*if*/

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
						}/*if*/
					   portfolio->volume = portfolio->volume + (stocktmp->close)*volume;
         			   tmpnode->next=tmp->curStock;
					   tmp->curStock=tmpnode;
   					   tmpnode=NULL;

					}/*if*/
				}/*while*/
			}/*if*/
		}/*if*/
		tmpnode=tmp->curStock;
		tmp=tmp->next;
	}/*if*/
}

void Portfolio::sell(Stock stock,float volume,string date)
{

	portfolionode *tmp = curPortfolio;
	portfolionode::stockinfo *tmpnode = tmp->curStock;
	Stock::node *stocktmp = stock.head;
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
		tmpnode=tmp->curStock;
		tmp=tmp->next;
	}
}

void Portfolio::Print()
{
	cout << "PRINT: " << endl;
	portfolionode *tmp = curPortfolio;
	portfolionode::stockinfo *infotmp = tmp->curStock;
   	 

    while(tmp!= NULL){
    	cout << "--- date: " << tmp->date << endl;
		while(infotmp!=NULL){
			cout<< "name: " << infotmp->name;
			cout<< ", volume: " << infotmp->volume << endl;
			infotmp=infotmp->next;
		}
    	infotmp=tmp->curStock;
		tmp=tmp->next;
   }
}


Portfolio::~Portfolio() {
}

