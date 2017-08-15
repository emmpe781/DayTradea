/*
 * Portfolio.cpp
 *
 *  Created on: 15 aug. 2017
 *      Author: Otur1337
 */

#include "Portfolio.h"

Portfolio::Portfolio() {
	cout << "initiating Portfolio... " << endl;
	head = NULL;
	tail = NULL;
}

void Portfolio::buyStock(Stock stock,int volume,string date)
{
	cout << "buying stock... "<< endl;

	Stock::node *stocktemp = stock.head;

	while(stocktemp!= NULL  && (stocktemp->date > date)){
		//ADD IF DATE ALREADY EXIST
		add_date(stocktemp->date,stock.name,volume);
		stocktemp=stocktemp->next;
	}

	stocktemp->next = NULL;

	if(stock.head == NULL)
	{
		stock.head = stocktemp;
		stock.tail = stocktemp;
	}
	else
	{
		stock.tail->next = stocktemp;
		stock.tail = stock.tail->next;
	}
}

void Portfolio::add_date(string date,string name,int volume)
{
	portfolionode *tmp = new portfolionode;
	portfolionode::stockinfo *infotemp = new portfolionode::stockinfo;

	tmp->date = date;

	infotemp->name = name;
	infotemp->volume = volume;

	infotemp->next = NULL;

	if(tmp->head == NULL)
	{
		tmp->head = infotemp;
		tmp->tail = infotemp;
	}
	else
	{
		tmp->tail->next = infotemp;
		tmp->tail = tmp->tail->next;
	}

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


void Portfolio::calculateValue(Stock stock)
{}

void Portfolio::Print()
{
	cout << "PRINT: " << endl;
	portfolionode *temp = head;
	portfolionode::stockinfo *infotemp = temp->head;

    while(temp!= NULL){
		infotemp=temp->head;
		cout<< "date: " << temp->date << endl;
		while(infotemp!=NULL){
			cout<< "name: " << infotemp->name << endl;
			cout<< "volume: " << infotemp->volume << endl;
			infotemp=infotemp->next;
		}
		temp=temp->next;
    }
}


/*
void Stock::buyStock(int volume,string date)
{
	cout << "buying stock: "<< endl;
    node *temp = head;
    while(temp!= NULL && (temp->date > date)){
    	temp->volume = temp->volume+volume;
    	temp->value=temp->volume*temp->close;
		temp=temp->next;
	}
}

void Stock::sellStock(int volume,string date)
{
	cout << "selling stock: "<< endl;
    node *temp = head;

    while(temp!= NULL && (temp->date > date)){
	    temp->volume = temp->volume-volume;
    	temp->value=temp->volume*temp->close;
	    temp=temp->next;
	 }
}
*/

Portfolio::~Portfolio() {
	// TODO Auto-generated destructor stub
}

