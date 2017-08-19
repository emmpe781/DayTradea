/*
 * Portfolio.cpp
 *
 *  Created on: 15 aug. 2017
 *      Author: Otur1337
 */

#include "Portfolio.h"

Portfolio::Portfolio(Stock stock,string date) {
	cout << "initiating Portfolio... " << endl;
	Stock::node *stocktmp = stock.head;

	while(stocktmp!= NULL){
		if (stocktmp->date > date){
			add_date(stocktmp->date,stock.name);
		}
		stocktmp=stocktmp->next;
	}
}

void Portfolio::add_date(string date,string name)
{
	portfolionode *tmp = new portfolionode;
	tmp->date = date;

	portfolionode::stockinfo *tmpnode = new portfolionode::stockinfo;

	tmpnode->name = name;
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

void Portfolio::buy(Stock stock,int volume,string date)
{

	portfolionode *tmp = head;
	portfolionode::stockinfo *tmpnode = tmp->head;

	while(tmp!= NULL){
		if (tmp->date >= date){
			tmpnode=tmp->head;
			cout << tmp->date <<endl;
			int stockexist = 0;
			//Check if the stock exist. If it exist it will be updated. If it does not exist it will be added.

			while (tmpnode != NULL){
				if (tmpnode->name==stock.name){
					tmpnode->volume = tmpnode->volume+volume;
					cout << tmpnode->volume <<endl;
					stockexist=1;
					break;
				}

				tmpnode=tmpnode->next;

				if ((tmpnode == NULL) && (stockexist==0)){
				   //The stock does not exist. creating new node"
				   tmpnode = new portfolionode::stockinfo;

				   tmpnode->name = stock.name;
				   tmpnode->volume = volume;
    			   tmpnode->next=tmp->head;
				   tmp->head=tmpnode;
				   tmpnode=NULL;
				 }
			}
		}
		tmp=tmp->next;
	}
}


void Portfolio::calculateValue()
{
	//  portfolionode *tmp = head;
	//	portfolionode::stockinfo *tmpnode = tmp->head;
	//	Stock::node *stocktmp = stock.head;

		/*while((tmp!= NULL) && (stocktmp != NULL)){
			if (tmp->date > date){
				while (tmp->date > stocktmp->date){
					stocktmp=stocktmp->next;
				}

				if (stocktmp->date == tmp->date){

				}
			}
			tmp=tmp->next;
			tmpnode=tmp->head;
		}
*/
}

void Portfolio::Print()
{
	cout << "PRINT: " << endl;
	portfolionode *tmp = head;
	portfolionode::stockinfo *infotmp = tmp->head;

    while(tmp!= NULL){
    	cout << "date in portfolio: " << tmp->date << endl;
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

