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
	void Buy_BearBull(Portfolio*,Stock*);
	virtual ~Algorithms();
};

#endif /* SRC_ALGORITHMS_H_ */
