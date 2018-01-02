#include "stock.h"
#include <iostream>

using namespace std;

Stock::Stock(void)
{
	head = NULL;
	tail = NULL;
	Stock::stockLength = 0;
}

void Stock::add_node_to_end(string date,float close)
{
	Stock::stockLength++;
	dayInfo *day_info = new dayInfo;
	day_info->date = date;
	day_info->close = close;
	day_info->est = 0;
	day_info->bearBull = 0;
	day_info->ma200 = 0;
	day_info->ma100 = 0;
	day_info->ma50 = 0;
	day_info->next = NULL;

	if(head == NULL)
	{
		head = day_info;
		tail = day_info;
	}
	else
	{
		tail->next = day_info;
		tail = tail->next;
	}
}

void Stock::Print()
{
	dayInfo *day_info = head;
    while(day_info!= NULL){
		cout<< "date: " << day_info->date;
		cout<< ", close: " <<  day_info->close << endl;
		day_info=day_info->next;
    }
}



