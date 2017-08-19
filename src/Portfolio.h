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
	  struct portfolionode{
		 string date;
		 struct stockinfo{
			 string name;
			 int volume;
			 stockinfo *next;
		 };
         stockinfo *head = NULL;
         stockinfo *tail = NULL;
		 portfolionode *next;
	  };
	portfolionode *head = NULL;
	portfolionode *tail = NULL;

	Portfolio(Stock,string);
	void Print();
	void add_date(string,string);
	void buy(Stock,int,string);
	void calculateValue();
	virtual ~Portfolio();
};

#endif /* SRC_PORTFOLIO_H_ */
