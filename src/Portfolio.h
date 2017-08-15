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
 		 stockinfo *head,*tail;
		 portfolionode *next;
	   };
	portfolionode *head,*tail;

	Portfolio();
	void Print();
	void add_date(string,string,int);

	void calculateValue(Stock);
	void buyStock(Stock,int,string);
	//void sellStock(Stock,int,string);


	virtual ~Portfolio();
};

#endif /* SRC_PORTFOLIO_H_ */
