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
#include<stdarg.h>

using namespace std;

class Plot
{
public:
	Plot();
	void Plot_port(Portfolio,Portfolio,Stock);
	void Plot_stocks(Stock,Stock);
	void PlotNodes(Stock,string);
	//stock, string som f�rklarar vad, default �r bara close
	//stock, ..., string
	virtual ~Plot();
};

#endif /* PLOT_H */

