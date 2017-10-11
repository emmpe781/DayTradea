#include "stock.h"
#include <iostream>

using namespace std;

Stock::Stock(void)
{
	firstStockDate = NULL;
	tail = NULL;
	Stock::stocklength = 0;
}

void Stock::add_node_to_end(string date,float close)
{
	Stock::stocklength++;
	node *date_node = new node;
	date_node->date = date;
	date_node->close = close;
	date_node->est = 0;
	date_node->bearBull = 0;
	date_node->ma200 = 0;
	date_node->ma100 = 0;
	date_node->ma50 = 0;
	date_node->next = NULL;

	if(firstStockDate == NULL)
	{
		firstStockDate = date_node;
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
	node *date_node = firstStockDate;
    while(date_node!= NULL){
		cout<< "date: " << date_node->date;
		cout<< ", close: " <<  date_node->close << endl;
		date_node=date_node->next;
    }
}



