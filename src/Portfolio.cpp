/*
 * Portfolio.cpp
 *
 *  Created on: 15 aug. 2017
 *      Author: Otur1337
 */
#define _USE_MATH_DEFINES
#include "Portfolio.h"
#include "matplotlibcpp.h"
#include <cmath>

namespace plt = matplotlibcpp;


Portfolio::Portfolio(ReadFile rf,string date) {
	cout << "initiating Portfolio... " << endl;
	Stock portf_time;
	string fname_time="../data/stockdata_Portfolio_fill.dat";
	rf.Read(fname_time,portf_time);

	Stock::node *stocktmp = portf_time.head;

	while(stocktmp!= NULL){
		if (stocktmp->date > date){
			add_date(stocktmp->date,"bank");
			
		}
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

void Portfolio::Plot()
{
	cout << "PRINT: " << endl;
	portfolionode *tmp = head;
	portfolionode::stockinfo *infotmp = tmp->head;
   	 
	int n=2130;
	vector<float> x(n),y(n); 
	float i = 0;
    while(tmp!= NULL){
		x.at(i) = i;//tmp->date;
		while(infotmp!=NULL){
			if (infotmp->name=="portfolio value"){
				y.at(i) = infotmp->volume;
				}
			infotmp=infotmp->next;
		}
		i=i+1;
    	infotmp=tmp->head;
		tmp=tmp->next;
   }

	plt::plot(x,y, "k-");
	
	plt::title("Portfolio");
	plt::save("./portfolio.png");
	plt::show();
}

Portfolio::~Portfolio() {
}

