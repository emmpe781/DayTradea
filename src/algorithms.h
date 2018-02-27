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
extern float constantA;
extern float constantB;                                    
extern float constantC;

const int RECALIBRATE = 1; //Omkalibrera portföljen

class Algorithms {
public:
    Algorithms();
    void CleanAlgorithms();
    float getPercentageOfOwnTime();
    float getIncreasePerYear(float, float);
    float getNrOfYears();
    bool TimeToRecalibrate;
    void updateStockDate(Stock[]);
    void Algo(string, Portfolio*, Stock[]);
    void Algo_BearBull(Portfolio*, 
                       Stock*, 
                       Portfolio::portfolionode*, 
                       Stock::dayInfo*);

    void CreateIndex(Portfolio*,Portfolio::portfolionode*, Stock[]);
    void BeatIndex(Portfolio*,Portfolio::portfolionode*, Stock[]);
    int MaxNumberOfStocks(const int, const int);
    void RecalibratePortfolio(Portfolio*,Portfolio::portfolionode*, Stock[]);
    void Sell_All(Portfolio*,Portfolio::portfolionode*, Stock[]);
    int NrOfStocks(Stock[]);
    bool SellStock(Stock[], int);

    struct RankStock{
        string stockName;
        float stockDelta200;
        float stockDelta50;
        float rankPoints;
        int rank;
        bool buyStock;
        bool exist;
        int counter;
    };
    int RemoveWorstStocks(RankStock rankStock[], int const removeStocks);

    virtual ~Algorithms();

};

#endif /* SRC_ALGORITHMS_H_ */
