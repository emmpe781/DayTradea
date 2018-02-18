/*
 * algorithms.cpp
 *
 *  Created on: 20 sep. 2017
 *      Author: Otur1337
 */

#include "algorithms.h"
#include "Portfolio.h"
#include "Stock.h"
#include "string"
#include "math.h"
using namespace std;
const Stock::dayInfo * lastStockDate = NULL;
int count = 0;
int countIndex = 0;



Algorithms::Algorithms() {
    // TODO Auto-generated constructor stub
    TimeToRecalibrate = true;
}

void Algorithms::updateStockDate(Stock stocks[])
{
    for (int i = 0; i < NROFSTOCKS; ++i)
    {
        Stock::dayInfo *curStocks = stocks[i].head;
        curStocks = curStocks->next;
        stocks[i].head = curStocks;
    }
}

void Algorithms::Algo(string algo, 
                      Portfolio *portfolio_p, 
                      Stock stocks[]) 
{
    Portfolio::portfolionode *curPortfolioDay = 
        portfolio_p->curPortfolio;

    Portfolio::portfolionode *previousPortfolioDay = 
        portfolio_p->curPortfolio; 


    //Borde vilja flytta in allt stockrelaterat till algoritmerna?!
    //Endast ha kvar hur portföljen uppdateras här ute?!
    Stock::dayInfo *curStocks = stocks[0].head;
    Stock::dayInfo *previousStocks = stocks[0].head;

    curPortfolioDay->portfolioValue = portfolio_p->cash;

    while(curPortfolioDay != NULL){
        
        portfolio_p->updateBeginningOfDay(previousPortfolioDay,
                                          curPortfolioDay, 
                                          stocks);
            
        if (algo == "BEARBULL")
        {
            //Kommer behöva anpassas till den mer generiska designen
            //Algo_BearBull(portfolio_p, &stocks[0], curPortfolioDay, index);
        }
        if (algo == "CREATEINDEX")
        {
            CreateIndex(portfolio_p, curPortfolioDay,stocks);
        }

        if (algo == "BEATINDEX")
        {
            BeatIndex(portfolio_p, curPortfolioDay,stocks);
        }

        //counter that controls how often
        //the portfolio shall recalib.
        ++count;
        updateStockDate(stocks);

        previousPortfolioDay=curPortfolioDay;
        curPortfolioDay=curPortfolioDay->next;
    }
}

void Algorithms::Algo_BearBull(Portfolio *portfolio_p, 
                               Stock *omxS30, 
                               Portfolio::portfolionode *tmpPortfolioDay,
                               Stock::dayInfo *index) {
    //Hur ska algen fungera?
    //1 loopa igenom alla datum i index
    //2 när index ligger i bull -> var 100 % investerad
    //3 när index ligger i bear -> var 0 & investerad
    float indexValue = index->close;

    if (index->bearBull == 1800){
        //cout << "BULL Handla!" << endl;
        float moneyToBuyWith = portfolio_p->cash;
        portfolio_p->buy(indexValue,omxS30->name,moneyToBuyWith, tmpPortfolioDay);
        //handla så många aktier du har råd att handla den dagen
    } 
    else { 
        //cout << "BEAR Handla inte!" << endl;
        if(tmpPortfolioDay->curStock != NULL)
        {
            portfolio_p->sell(index,omxS30->name,1, tmpPortfolioDay);
        }
    }
}
/*
int Algorithms::MaxNumberOfStocks(const float money, const float priceOfStock)
{
    float nrOfStocks = 0;
    nrOfStocks = money/priceOfStock; 
    return (int)floor(nrOfStocks);
}
*/

void Algorithms::Sell_All(  Portfolio *portfolio_p, 
                            Portfolio::portfolionode *curPortfolioDay,
                            Stock stocks[])
{
    for(int i = 0; i < NROFSTOCKS; ++i)
        {

            Stock::dayInfo *curStock = stocks[i].head;
            string stockName = stocks[i].name;

            if (!(curStock->exist))
            {
                continue;
            }
            Portfolio::portfolionode *tmp = curPortfolioDay;

            portfolio_p->sell(curStock, stockName, 
                              1, tmp);  

        }
}

int Algorithms::NrOfStocks(Stock stocks[])
{
    int nrOfStocks = 0;
    for (int i = 0; i < NROFSTOCKS; ++i)
    {
        if (stocks[i].head->exist == true)
        {
            ++nrOfStocks;
        }
    }

    //cout << "The number of existing stocks are: " << nrOfStocks << endl;
    return nrOfStocks;
}

void Algorithms::RecalibratePortfolio(Portfolio *portfolio_p, 
                                      Portfolio::portfolionode *curPortfolioDay,
                                      Stock stocks[]) {

    
    int nrOfActiveStocks = NrOfStocks(stocks);


    
    Sell_All(portfolio_p, curPortfolioDay, stocks);

    float moneyToBuyWith = portfolio_p->cash;

    float moneyForEachStock = moneyToBuyWith/nrOfActiveStocks;

    //cout << "Buy the following stocks after RecalibratePortfolio: " << endl << endl;
    //int nrOfActiveStocks = 0;

    
    for(int i = 0; i < NROFSTOCKS; ++i)
    {
        Stock::dayInfo *curStock = stocks[i].head;
        string stockName = stocks[i].name;
        float stockValue = curStock->close;


        if (!(curStock->exist)) 
        {
            continue;
        }

        Portfolio::portfolionode *tmp = curPortfolioDay;

        //Printing the amount of each stock
        portfolio_p->buy(stockValue, stockName, 
                         moneyForEachStock, tmp);
        
    }
                        
    //cout << endl << endl << endl; 
    TimeToRecalibrate = false;
}


void Algorithms::CreateIndex(Portfolio *portfolio_p, Portfolio::portfolionode *curPortfolioDay, Stock stocks[]) 
{
    if(count % RECALIBRATE == 0)
    {
        TimeToRecalibrate = true;
    }

    if(TimeToRecalibrate)
    {
        RecalibratePortfolio(portfolio_p,curPortfolioDay,stocks);

    }
    ++countIndex;
}

int Algorithms::RemoveWorstStocks(RankStock rankStock[], int const removeStocks)
{
    int nrOfRemovedStocks = 0;
    int nrOfWorseStocks = 0;

    for(int i = 0; i < NROFSTOCKS; ++i)
    {
        

        if(rankStock[i].buyStock == false)
        {
            continue;
        }

        for(int j = 0; j < NROFSTOCKS; ++j)
        {
            //Kolla om det finns sämre aktier
            if (rankStock[i].rankPoints > rankStock[j].rankPoints)
            {
                ++nrOfWorseStocks;
            }
        }
        //cout << "Nr of worse stocks = " << nrOfWorseStocks << "aktie = " 
        //     << rankStock[i].stockName << "Rank = " << rankStock[i].rankPoints << endl; 

        //Om "vi" är en av de två sämsta aktierna
        if(removeStocks > nrOfWorseStocks)
        {
            /*cout << "Remove Stock, " << rankStock[i].stockName
                 << "rankPoints = " << rankStock[i].rankPoints << endl << endl;*/
            rankStock[i].buyStock = false;
            
            ++nrOfRemovedStocks;
        }
        nrOfWorseStocks = 0;

    }
    //cout << " nrOfRemovedStocks OTUR = " << nrOfRemovedStocks << endl;
    return nrOfRemovedStocks;
}

bool Algorithms::SellStock(Stock *stock, const bool ownStock)
{
    //float ma200   = stock->head->ma200;
    //float ma50   = stock->head->ma50;
    float delta200   = stock->head->delta200;
    float closeValue = stock->head->close;

    static int counter = 0;
    float sumDiffCloseMa50 = 0;
    float sumDiffMa50Ma200 = 0;
    static bool own_Stock = true;
    

    const int days = 15;
    static float deltaCloseMa50[days] = {0};
    static float deltaMa50Ma200[days] = {0};
    static float maDays[days] = {0};

    const int _200 = 200;
    static float MA200[_200] = {closeValue};

    const int _50 = 50;
    static float MA50[_50] = {closeValue};


    float sumMaDays = 0;
    float ma200 = 0;
    float ma50 = 0;

    


    MA200[counter % _200] = closeValue;
    MA50[counter % _50] = closeValue;

    //Calculate ma50
    for (int i = 0; i < _50; ++i)
    {
        ma50 = ma50 + (float) MA50[i]/_50;
    }

    //Calculate ma200
    for (int i = 0; i < _200; ++i)
    {
        ma200 = ma200 + MA200[i]/_200;
    }


    deltaCloseMa50[counter % days] = closeValue - ma50;
    deltaMa50Ma200[counter % days] = ma50 - ma200;
    maDays[counter % days] = closeValue;

    for (int i = 0; i < days; ++i)
    {
        sumDiffCloseMa50 = sumDiffCloseMa50 + deltaCloseMa50[i];
        sumDiffMa50Ma200 = sumDiffMa50Ma200 + deltaMa50Ma200[i];
        sumMaDays = sumMaDays + maDays[i]/days;

    }
    ++counter;

    //cout << " sumDiff = " << sumDiff << endl;
    
    //Gör en casesats så bull-attributet kan hanteras som en statemaskin!
    //static bool bull[NROFSTOCKS] = {true};
    static int i = 0;
    bool sellStock = false;


    sellStock = false;

    //SELL
    if (sumDiffCloseMa50 < 10 && 
        own_Stock == true &&
        sumDiffMa50Ma200 < 10 && 
        closeValue < sumMaDays)
    {
        //if(ma200 > ma50 && closeValue > ma50) {
            
            //Köp
            cout << "--------------- Sälj: " << stock->name << "date : "
                << stock->head->date<< " ---------- "<< endl << endl 
                << "Close = " << closeValue << ", "<< endl << "ma50 = " 
                << ma50  << ", " << endl << "ma200 = " << ma200 << endl 
                <<  ", " << "sumDiffCloseMa50 =  "  << sumDiffCloseMa50 << endl;
        own_Stock = false;
        sellStock = true;
    }

    //BUY
    if (sumDiffCloseMa50 > 0 && 
        own_Stock == false && 
        sumDiffMa50Ma200 > 0 && 
        closeValue > sumMaDays)
    {
        own_Stock = true;
        sellStock = false;
    }
    return !own_Stock;

}

void Algorithms::BeatIndex(Portfolio *portfolio_p, 
                           Portfolio::portfolionode *curPortfolioDay, 
                           Stock stocks[]) 
{
    static int initValues = 0;

    //RECALIBRATE is defined in algorithms.h
    if(count % RECALIBRATE != 0)
    {
        return;
    }


    Sell_All(portfolio_p, curPortfolioDay, stocks);

    RankStock rankStock[NROFSTOCKS];


    //Populate Stocks With DeltaValues
    for(int i = 0; i < NROFSTOCKS; ++i)
    {
        Stock::dayInfo *curStock   = stocks[i].head;
        rankStock[i].exist         = curStock->exist;
        rankStock[i].stockName     = stocks[i].name;
        rankStock[i].stockDelta200 = curStock->delta200;
        rankStock[i].stockDelta50  = curStock->delta50;

        //Rör inte rankpoints förens delta200 får värden.
        if (curStock->delta200 != 0)
        {
            rankStock[i].rankPoints    = (curStock->delta200)*3 + curStock->delta50;

            /*cout << stocks[i].name << endl;
            cout << " curStock->delta200 = " << curStock->delta200;
            cout << ",    curStock->delta50 = " << curStock->delta50 << endl << endl;*/

        }
        
        if (initValues == 0)
        {
            cout << "INIT rankStock[].buystock" << endl;
            rankStock[i].rank     = 0;
            rankStock[i].buyStock = false;
        }
        
    }
    ++initValues;

    int nrOfStocksToBuy = 0;
    
    //Chose which stocks to buy
    for(int i = 0; i < NROFSTOCKS; ++i)
    {
        if (rankStock[i].exist == false)
        {
            continue;
        }

        if(SellStock(&stocks[i], rankStock[i].buyStock))
        {
            //Do not buy this Stock            
            rankStock[i].buyStock = false;
        }
        
        else
        {
            //Buy This Stock
            rankStock[i].buyStock = true;
            ++nrOfStocksToBuy;
            //cout << "nrOfStocksToBuy " << nrOfStocksToBuy << endl;
        }
    }


    float moneyToBuyWith = portfolio_p->cash;
    float moneyForEachStock = moneyToBuyWith/nrOfStocksToBuy;

    for(int i = 0; i < NROFSTOCKS; ++i)
    {
        Stock::dayInfo *curStock = stocks[i].head;
        string stockName = stocks[i].name;
        float stockValue = curStock->close;


        if (!(curStock->exist)) 
        {
            continue;
        }

        if (rankStock[i].buyStock == true)
        {
            Portfolio::portfolionode *tmp = curPortfolioDay;
            portfolio_p->buy(stockValue, rankStock[i].stockName, 
                             moneyForEachStock, tmp);
        }

        
        
    }



}



Algorithms::~Algorithms() {
    // TODO Auto-generated destructor stub
}


/*      cout << "--------------- PRINTING START --------------------" << endl;
        tmpStock = tmpPortfolioDay->curStock;

        cout << "Cash: " <<  portfolio_p->cash << endl;
        cout << "Date: " <<  tmpPortfolioDay->date << endl;
        cout << "PortfolioValue: " <<  tmpPortfolioDay->portfolioValue << endl;
        while(tmpStock != NULL){
            cout << "  StockName: " <<  tmpStock->name << endl;
            cout << "  NrOfStocks: " <<  tmpStock->nrOfStocks << endl;
            cout << "  --  " << endl;

            tmpStock = tmpStock->next;
        }
        cout << "--------------- PRINTING END --------------------" << endl;
*/