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
		 float portfolioValue; //The amount of money + stockValue for each date 
		 					   //porfolioValue=cash+"value of all stocks in portfolio"
		 float normValue;
		 struct stockinfo{
			 string name;
			 float stockValue; ///REMOVE
			 int nrOfStocks;
			 stockinfo *next;
		 };

         stockinfo *curStock = NULL;
         stockinfo *tail = NULL;

		 portfolionode *next;
	  };

	portfolionode *curPortfolio = NULL; //Current Portfolio Content
	portfolionode *tail = NULL; 

	Portfolio(string);
	void Print();
	bool stockInPortfolio(string,Portfolio::portfolionode::stockinfo*);
	void setStartValue(float);
	void add_date(string);
	void buy(float, string, float, Portfolio::portfolionode*);
	void updateBeginningOfDay(Portfolio::portfolionode*, 
							  Portfolio::portfolionode*, 
							  Stock[]);
	void updateBeginningOfDay2(Portfolio::portfolionode*, Stock[]);
	void sell(Stock::dayInfo*,string,int, Portfolio::portfolionode*);
	int NrOfStocksInPortfolio(Portfolio::portfolionode*, string);
	int stockValue(Portfolio::portfolionode*, Stock[]);
	virtual ~Portfolio();
};

#endif /* SRC_PORTFOLIO_H_ */
