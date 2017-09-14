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
         stockinfo *head = NULL;
         stockinfo *tail = NULL;
		 portfolionode *next;
	  };
	portfolionode *head = NULL;
	portfolionode *tail = NULL;

	Portfolio(ReadFile,string);
	void Print();

	void add_date(string,string);
	void add_to_bank(float,string);
	void remove_from_bank(float,string);
	void insert_end(string);
	void insert_start(string);

	void buy(Stock,float,string);
	void calculateValue();
	virtual ~Portfolio();
};

#endif /* SRC_PORTFOLIO_H_ */
