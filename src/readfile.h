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

class ReadFile
{
public:
	ReadFile();
	void Read(string,Stock&);
	void ExtractDayData(string,Stock&);
	void ExtractStockData(string,Stock&);
	virtual ~ReadFile();
};

#endif /* READFILE_H */
