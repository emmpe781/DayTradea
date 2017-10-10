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

	  struct portfolionode{
		 string date;
		 struct stockinfo{
			 string name;
			 float volume;
			 stockinfo *next;
		 };

         stockinfo *curStock = NULL;
         stockinfo *tail = NULL;
		 portfolionode *next;
	  };

	typedef portfolionode* portfolionode_p;

	portfolionode *curPortfolio = NULL;
	portfolionode_p curPortfolio_p = NULL; //Current Portfolio Content
	portfolionode *tail = NULL; //Not Used

	Portfolio(string);
	void Print();

	void add_date(string,string);
	void add_to_bank(float,string);
	void remove_from_bank(float,string);
	void insert_end(string);
	void insert_start(string);

	void buy(Stock,float,string);
	void sell(Stock,float,string);

	void calculateValue();
	virtual ~Portfolio();
};

#endif /* SRC_PORTFOLIO_H_ */
