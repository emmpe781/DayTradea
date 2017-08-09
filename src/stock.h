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
		  int volume;
		  double close;
		  node *next;
		  //node *previous;
	  };
		node *head,*tail;
		Stock();
		void add_node(string,double,int);
		void Print();
		void buyStock(int,string);
		void sellStock(int,string);

};

#endif /* STOCK_H */
