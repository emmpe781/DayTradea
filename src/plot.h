/*
 * ReadFile.h
 *
 *  Created on: 3 juni 2017
 *      Author: Otur1337
 */

#ifndef PLOT_H
#define PLOT_H
#include <string>
#include "stock.h"
#include "Portfolio.h"

using namespace std;

class Plot1
{
public:
	Plot1();
	void plotta(Portfolio,Stock);
	virtual ~Plot1();
};

#endif /* PLOT_H */

