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


/*void Stock::Plot()
{
	node *tmp = head;
	cout << "PRINT: " << endl;

	int n=2130;
	vector<int> x(n);
	vector<double> y(n);
	vector<string> t(n);
	float i = 0;
    while(tmp!= NULL){
		x.at(i) = i;
		t.at(i) = tmp->date;
		y.at(i) = tmp->close;
		i=i+1;
		tmp=tmp->next;
   }



	//	plt::xticks()
	//plt::xticks(x,t);
	plt::plot(x,y, "k-");

    //plt::plot({"1","2","3","4"},{1,3,2,4},"k");
	//plt::grid(true);
	//plt::title("Portfolio");
	//plt::tight_layout();
	//plt::save("./portfolio.png");
	//plt::show();
}*/

