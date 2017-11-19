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
		#define BEAR 10;
		#define BULL 1800;


	  string name;
	  int stocklength;	  
	  struct node{
		  string date;
		  float close;
		  float est;
		  //0=unknown, 1800 = bull, 2 = bear
		  int bearBull;
		  float ma200;
		  float ma100;
		  float ma50;
		  node *next; //Ta bort på sikt! mot nextDate
		  node *nextDate;
	  };
	  node *firstStockDate;
	  node *tail;
	  Stock();
	  float stockValue(string ,string);
	  void add_node_to_end(string,float);
	  void Print();
};
typedef Stock* Stock_p;

#endif /* STOCK_H */
