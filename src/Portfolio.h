/*
 * Portfolio.h
 *
 *  Created on: 15 aug. 2017
 *      Author: Otur1337
 */
#include "stock.h"
#include "readfile.h"


#ifndef SRC_PORTFOLIO_H_
#define SRC_PORTFOLIO_H_


class Portfolio {
public:

	  string portfolioname;
	  int portfoliolength;
	  float portfolioMoney; //The amount of money
	  struct portfolionode{
		 string date;
		 struct stockinfo{
			 string name;
			 float stockValue;
			 int nrOfStocks;
			 stockinfo *next;
		 };

		 float totalValue; //The amount of money + stockValue for each date
         stockinfo *curStock = NULL;
         stockinfo *nextStock = NULL;
         stockinfo *tail = NULL;
         stockinfo myStockinfo;
		 portfolionode *next;
	  };

	typedef portfolionode* portfolionode_p;

	portfolionode_p curPortfolio = NULL; //Current Portfolio Content
	portfolionode* test;
	portfolionode *tail = NULL; //Not Used

	Portfolio(string);
	void Print();
	bool stockInPortfolio(string,Portfolio::portfolionode::stockinfo*);
	void setStartValue(float);
	void add_date(string,string);
	void add_to_bank(float,string);
	void remove_from_bank(float,string);
	void insert_end(string);
	void insert_start(string);


	void buy2(Stock*, float, string);
	void buy3(Stock::node*,string,float, Portfolio::portfolionode*);
	float portfolioValue(Portfolio* ,string);
	void buy(Stock,float,string);
	void sell(Stock,float,string);
	virtual ~Portfolio();
};
typedef Portfolio* Portfolio_p;

#endif /* SRC_PORTFOLIO_H_ */
