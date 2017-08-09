#include "stock.h"
#include <iostream>
using namespace std;

Stock::Stock(void)
{
	head = NULL;
	tail = NULL;
}

void Stock::add_node(string date,double close,int volume)
{
	node *tmp = new node;
	tmp->date = date;
	tmp->close = close;
	tmp->volume=volume;
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

void Stock::Print()
{
	node *temp = head;
    while(temp!= NULL){
    cout<< "date: " << temp->date;
    cout<< ", close: " <<  temp->close;
    cout<< ", volume: " <<  temp->volume<<endl;
    temp=temp->next;
    }
}

void Stock::buyStock(int volume,string date)
{
	cout << "buying new stock: "<< endl;
    node *temp = head;
    while(temp!= NULL && (temp->date > date)){
    	temp->volume = temp->volume+volume;
		temp=temp->next;
	}
}

void Stock::sellStock(int volume,string date)
{
	cout << "buying new stock: "<< endl;
    node *temp = head;

    while(temp!= NULL && (temp->date > date)){
	    temp->volume = temp->volume-volume;
	    temp=temp->next;
	 }
}
