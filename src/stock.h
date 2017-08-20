#ifndef STOCK_H
#define STOCK_H

#include <list>
#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>


using namespace std;

class Stock{
	public:
	  string name;
	  struct node{
		  string date;
		  float close;
		  node *next;
	  };
		node *head,*tail;
		Stock();
		void add_node(string,float);
		void Print();
};

#endif /* STOCK_H */
