#include "stock.h"
#include <iostream>
using namespace std;

Stock::Stock(void)
{
	head = NULL;
	tail = NULL;
}

void Stock::add_node(string date,double close)
{
	node *tmp = new node;
	tmp->date = date;
	tmp->close = close;
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
    cout<< "date: " << temp->date<< endl;
    cout<< ", close: " <<  temp->close << endl;
    temp=temp->next;
    }
}

