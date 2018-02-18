#ifndef STOCK_H
#define STOCK_H

#include <list>
#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>


using namespace std;
const int NROFSTOCKS = 1;

class Stock{
	public:
		#define BEAR 10;
		#define BULL 1800;


	  string name;
	  int stockLength;	  
	  struct dayInfo {
		  string date;
		  bool exist;
		  float close;
		  float norm;
		  float est;
		  //0=unknown, 1800 = bull, 2 = bear
		  int bearBull;
		  float ma200;
		  float ma100;
		  float ma50;
		  float delta200; //Derivatan
		  float delta100;
		  float delta50;
		  dayInfo *next;
	  };
	  dayInfo *head;
	  dayInfo *tail;
	  Stock();
	  float stockValue(string ,string);
	  void add_node_to_end(string,float,string);
	  void Print();
};

#endif /* STOCK_H */
