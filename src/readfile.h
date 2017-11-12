/*
 * ReadFile.h
 *
 *  Created on: 3 juni 2017
 *      Author: Otur1337
 */

#ifndef READFILE_H
#define READFILE_H
#include <string>
#include "stock.h"

using namespace std;

class ReadFile1
{
public:
	ReadFile1();
	void Read(string,Stock *,string);
	void PopulateStock(Stock *);
	void ExtractDayData(string,Stock*,string);
	void ExtractStockData(string,Stock*,string);
	void ExpectedValue(Stock*,float);
	void BearBull(Stock*);
	void ExpectedValue2(Stock*,float);
	void Mean(Stock*,int);
	void nyfunction(){}
	virtual ~ReadFile1();

};

#endif /* READFILE_H */

