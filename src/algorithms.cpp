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

static int noOwnCounter = 1;
static int ownCounter = 1;
static float firstStockValue = 0;
static float lastStockValue = 0;
static float totalIncrease = 0;
static float nrOfYears = 0;




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

float Algorithms::getNrOfYears()
{
    static int totalDays = 0;
    static float years = 0;
    totalDays = noOwnCounter + ownCounter;
    years = (float) totalDays/365;
    
    return years;

}

float Algorithms::getPercentageOfOwnTime()
{
    static int totalDays = 0;
    static float percOwnStock;
    
    totalDays = noOwnCounter + ownCounter;
    percOwnStock = (float) ownCounter/totalDays;

    return percOwnStock;
}

float Algorithms::getIncreasePerYear(float increaseFactor, float years)
{
    static float increasePerYear = 0;

    increasePerYear = pow(increaseFactor, (1/years));
    return increasePerYear;
}



void Algorithms::Algo(string algo, 
                      Portfolio *portfolio_p, 
                      Stock stocks[]) 
{
    Portfolio::portfolionode *curPortfolioDay = 
        portfolio_p->curPortfolio;

    Portfolio::portfolionode *previousPortfolioDay = 
        portfolio_p->curPortfolio; 

    static float totalIncreaseStock = 0;
    static float percentageOfOwnStockTime = 0;
    static float portfValue = 0;
    static float startPortfValue = 0;
    static float portfIncrease = 0;
    static float stockIncreasePerYear = 0;
    static float portfIncreasePerYear = 0;


    startPortfValue = portfolio_p->cash;

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

        portfValue = curPortfolioDay->portfolioValue;

        previousPortfolioDay=curPortfolioDay;
        curPortfolioDay=curPortfolioDay->next;
    }

    nrOfYears = getNrOfYears();

    //För vanliga aktien
    totalIncreaseStock = lastStockValue/firstStockValue;
    //getIncreasePerYear(totalIncreaseFactor, nrOfYears);
    stockIncreasePerYear = getIncreasePerYear(totalIncreaseStock, nrOfYears);


    //För aktien i samband med algoritm:
    portfIncrease = portfValue/startPortfValue;
    percentageOfOwnStockTime = getPercentageOfOwnTime();
    portfIncreasePerYear = getIncreasePerYear(portfIncrease, percentageOfOwnStockTime*nrOfYears);

    cout << " stockIncreasePerYear = " << stockIncreasePerYear << endl;
    cout << " portfIncreasePerYear = " << portfIncreasePerYear << endl;
    
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

    return nrOfStocks;
}

void Algorithms::RecalibratePortfolio(Portfolio *portfolio_p, 
                                      Portfolio::portfolionode *curPortfolioDay,
                                      Stock stocks[]) {


    int nrOfActiveStocks = NrOfStocks(stocks);
    Sell_All(portfolio_p, curPortfolioDay, stocks);


    float moneyToBuyWith = portfolio_p->cash;

    float moneyForEachStock = moneyToBuyWith/nrOfActiveStocks;


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
                        
    TimeToRecalibrate = false;
}


void Algorithms::CreateIndex(Portfolio *portfolio_p, 
                             Portfolio::portfolionode *curPortfolioDay, 
                             Stock stocks[]) 
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

bool Algorithms::SellStock(Stock *stock)
{
    //float ma200   = stock->head->ma200;
    //float ma50   = stock->head->ma50;

    float delta200   = stock->head->delta200;
    float closeValue = stock->head->close;
    float estStock   = stock->head->ma300;

    static bool initialStockValue = true;
    static int stockCounter = 0;

    static int counter = 0;
    static bool own_Stock[NROFSTOCKS] = {true};

    const int _200 = 200;
    const int _50  = 50;
    const int _25  = 25;
    
    static float LAST200DAYS[ NROFSTOCKS ][ _200 ] = {closeValue};
    static float LAST50DAYS[  NROFSTOCKS ][ _50 ]  = {closeValue};
    static float LAST25DAYS[  NROFSTOCKS ][ _25 ]  = {closeValue};

    static float ma200[ NROFSTOCKS ][ _200]  = {0};
    static float ma50 [ NROFSTOCKS ][ _50]   = {0};
    static float ma25 [ NROFSTOCKS ][ _25]   = {0};

    static float oldMa200[NROFSTOCKS] = {0};
    static float oldMa50[NROFSTOCKS]  = {0};
    static float oldMa25[NROFSTOCKS]  = {0};

    static bool crash[NROFSTOCKS] = {false};

    static float lokMax[NROFSTOCKS] = {0};
    static float lokMin[NROFSTOCKS] = {0};
    static bool posDirection[NROFSTOCKS] = {true};



    
    LAST200DAYS[stockCounter][counter % _200] = closeValue;
    ma200[ stockCounter ][counter % _200] = 0;

    LAST50DAYS[stockCounter][counter % _50] = closeValue;
    ma50[ stockCounter ][counter % _50] = 0;

    LAST25DAYS[stockCounter][counter % _25] = closeValue;
    ma25[ stockCounter ][counter % _25] = 0;
    

    if (initialStockValue == true)
    {
        firstStockValue = closeValue;
        initialStockValue = false;
    }
    lastStockValue = closeValue;


    //Calculate ma25[ stockCounter ]
    for (int i = 0; i < _25; ++i)
    {
        ma25[ stockCounter ][counter % _25] = 
          ma25[ stockCounter ][counter % _25] + (float) LAST25DAYS[stockCounter][i]/_25;
    }


    //Calculate ma50
    for (int i = 0; i < _50; ++i)
    {
        ma50[ stockCounter ][counter % _50] = 
          ma50[ stockCounter ][counter % _50] + (float) LAST50DAYS[stockCounter][i]/_50;
    }


    //Calculate ma200
    for (int i = 0; i < _200; ++i)
    {
        ma200[ stockCounter ][counter % _200] = 
          ma200[ stockCounter ][counter % _200] + (float) LAST200DAYS[stockCounter][i]/_200;
    }
    

    //MAX Value,
    if ((oldMa200[stockCounter] > ma200[ stockCounter ][counter % _200]) && 
        posDirection[ stockCounter ])
        
    {
        lokMax[ stockCounter ] = ma200[ stockCounter ][counter % _200];
        posDirection[ stockCounter ] = false;
    }


    

    //MIN Value
    if ((oldMa200[stockCounter] < ma200[ stockCounter ][counter % _200]) && 
        (!posDirection[ stockCounter ]))
    {
        lokMin[ stockCounter ] = ma200[ stockCounter ][counter % _200];
        posDirection[ stockCounter ] = true;
    }

    if ((1.2*ma200[ stockCounter ][counter % _200] < lokMax[ stockCounter ]) && 
        (posDirection[ stockCounter ] == false))
    {
        crash[ stockCounter ] = true;
    }

    if (crash[ stockCounter ] == false)
    {


        bool SELL = (own_Stock[ stockCounter ] == true &&
                     closeValue < estStock*0.95);



        bool BUY = (own_Stock[ stockCounter ] == false &&
                    ma200[ stockCounter ][counter % _200] > 1.04*lokMin[ stockCounter ] && 
                    closeValue > estStock);



        //SELL
        if (SELL)
        {
            own_Stock[ stockCounter ] = false;
        }

        //BUY
        if (BUY)
        {
            own_Stock[ stockCounter ] = true;
        }
    }

    else
    {
        if(ma200[ stockCounter ][counter % _200] > estStock)
        {
            crash[ stockCounter ] = false;
        }
        

       //BUY
       if (own_Stock[ stockCounter ] == false &&
           oldMa50[stockCounter] < ma50[ stockCounter ][counter % _50] &&
           oldMa25[stockCounter] < ma25[ stockCounter ][counter % _25])
       {
            own_Stock[ stockCounter ] = true;
       }

       //SELL
       if (own_Stock[ stockCounter ] == true &&
           oldMa200[stockCounter] > ma200[ stockCounter ][counter % _200] &&
           oldMa50[stockCounter] > ma50[ stockCounter ][counter % _50] &&
           oldMa25[stockCounter] > ma25[ stockCounter ][counter % _25])
       {
            own_Stock[ stockCounter ] = false;
       }


    }


    oldMa200[stockCounter] = ma200[ stockCounter ][counter % _200];
    oldMa50[stockCounter]  = ma50[ stockCounter ][counter % _50];
    oldMa25[stockCounter]  = ma25[ stockCounter ][counter % _25];

    if (own_Stock[ stockCounter ])
    {   
        ++ownCounter;

    }
    else 
    {
        ++noOwnCounter;
    }


    //last stock
    if(stockCounter == NROFSTOCKS-1)
    {
        ++counter;    
    }

    ++stockCounter;
    stockCounter = stockCounter % NROFSTOCKS;


    return !own_Stock[ stockCounter ];


}

void Algorithms::BeatIndex(Portfolio *portfolio_p, 
                           Portfolio::portfolionode *curPortfolioDay, 
                           Stock stocks[]) 
{

    const float moneyToBuyWith       = portfolio_p->cash;
    cout << "portfolio_p->cash = " << portfolio_p->cash << endl;

    static bool buyStock[NROFSTOCKS] = {false};

    float moneyForEachStock    = 0;
    int   nrOfStocksToBuy      = 0;


    //RECALIBRATE is defined in algorithms.h
    if(count % RECALIBRATE != 0)
    {
        return;
    }

    Sell_All(portfolio_p, curPortfolioDay, stocks);

    //Chose which stocks to buy
    for(int i = 0; i < NROFSTOCKS; ++i)
    {
        if (stocks[i].head->exist == false)
        {
            continue;
        }

        if(SellStock(&stocks[i]))
        {
            //Do not buy this Stock
            buyStock[i] = false;

        }
        
        else
        {
            //Buy This Stock
            buyStock[i] = true;
            ++nrOfStocksToBuy;
        }
        
    }

    //Nothing to buy
    if (nrOfStocksToBuy == 0)
    {
        return;   
    }

    moneyForEachStock = moneyToBuyWith/nrOfStocksToBuy;
    /*cout << "moneyToBuyWith = " << moneyToBuyWith << endl;
    cout << "nrOfStocksToBuy = " << nrOfStocksToBuy << endl;
    cout << "moneyForEachStock = " << moneyForEachStock << endl;*/

    for(int i = 0; i < NROFSTOCKS; ++i)
    {
        Stock::dayInfo *curStock = stocks[i].head;

        string stockName         = stocks[i].name;
        float stockValue         = curStock->close;


        if (!(curStock->exist)) 
        {
            continue;
        }

        if (buyStock[i] == true)
        {
            Portfolio::portfolionode *tmp = curPortfolioDay;
            portfolio_p->buy(stockValue, stockName, 
                             moneyForEachStock, tmp);
        }
    }

}



Algorithms::~Algorithms() {
    // TODO Auto-generated destructor stub
}