#include "stock.h"
#include <iostream>
using namespace std;

Stock::Stock(void)
{
	head = NULL;
	tail = NULL;
}

void Stock::add_node_to_end(string date,float close)
{
	node *date_node = new node;
	date_node->date = date;
	date_node->close = close;
	date_node->next = NULL;

	if(head == NULL)
	{
		head = date_node;
		tail = date_node;
	}
	else
	{
		tail->next = date_node;
		tail = tail->next;
	}
}

void Stock::Print()
{
	node *date_node = head;
    while(date_node!= NULL){
		cout<< "date: " << date_node->date;
		cout<< ", close: " <<  date_node->close << endl;
		date_node=date_node->next;
    }
}

