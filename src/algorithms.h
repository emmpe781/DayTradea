/*
 * algorithms.h
 *
 *  Created on: 20 sep. 2017
 *      Author: Otur1337
 */

#ifndef SRC_ALGORITHMS_H_
#define SRC_ALGORITHMS_H_
#include "Portfolio.h"

using namespace std;


class Algorithms {
public:
	Algorithms();
	bool TimeToRecalibrate;
	void updateStockDate(Stock[]);
	void Algo(string, Portfolio*, Stock[]);
	void Algo_BearBull(Portfolio*, 
					   Stock*, 
		               Portfolio::portfolionode*, 
		               Stock::dayInfo*);

	void CreateIndex(Portfolio*,Portfolio::portfolionode*, Stock[]);
	int MaxNumberOfStocks(const int, const int);
	void RecalibratePortfolio(Portfolio*,Portfolio::portfolionode*, Stock[]);
	void Sell_All(Portfolio*,Portfolio::portfolionode*, Stock[]);

	void SlayIndex(Portfolio*,Stock*);
	virtual ~Algorithms();

};

#endif /* SRC_ALGORITHMS_H_ */
