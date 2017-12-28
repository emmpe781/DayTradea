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
      float cash; //The amount of money

	  struct portfolionode{
		 string date;
		 float portfolioValue; //The amount of money + stockValue for each date   porfolioValue=cash+"value of all stocks in portfolio"

		 struct stockinfo{
			 string name;
			 float stockValue; ///REMOVE
			 int nrOfStocks;
			 stockinfo *next;
		 };

         stockinfo *curStock = NULL;
         stockinfo *tail = NULL;
         stockinfo myStockinfo;
		 portfolionode *next;
	  };

	typedef portfolionode* portfolionode_p;

	portfolionode_p curPortfolio = NULL; //Current Portfolio Content
	portfolionode *tail = NULL; //Not Used

	Portfolio(string);
	void Print();
	bool stockInPortfolio(string,Portfolio::portfolionode::stockinfo*);
	void setStartValue(float);
	void add_date(string);
	void buy(Stock::node*,string,float, Portfolio::portfolionode*, Portfolio*);
	void updateBeginningOfDay(Portfolio::portfolionode*,Portfolio::portfolionode*,Stock::node*,Stock::node*);
	void sell(Stock::node*,string,int, Portfolio::portfolionode*, Portfolio*);
	virtual ~Portfolio();
};
typedef Portfolio* Portfolio_p;

#endif /* SRC_PORTFOLIO_H_ */
