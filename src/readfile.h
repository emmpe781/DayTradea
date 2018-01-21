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
#include "portfolio.h"
using namespace std;

class ReadFile
{
public:
	ReadFile();
	void Read(string,Stock *,string);
	void PopulateStock(Stock *);
	void ExtractDayData(string,Stock*,string);
	void ExtractStockData(string,Stock*,string);
	void ExpectedValue(Stock*,float);
	void BearBull(Stock*);
	void ExpectedValue2(Stock*,float);
	void Mean(Stock*,int);
	void Normalized(Stock*);
	void NormalizedPort(Portfolio*);
	virtual ~ReadFile();

};

#endif /* READFILE_H */

