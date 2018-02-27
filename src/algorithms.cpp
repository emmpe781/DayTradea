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
int days = 0;

static int noOwnCounter = 1;
static int ownCounter = 1;
static float firstStockValue = 0;
static float lastStockValue = 0;
static float totalIncrease = 0;
static float nrOfYears = 0;
static int sellStockCounter = 0;
static bool own_Stock[NROFSTOCKS];

static const int _200 = 200;
static const int _50  = 50;
static const int _25  = 25;

static float LAST200DAYS[ NROFSTOCKS ][ _200 ] = {0};
static float LAST50DAYS[  NROFSTOCKS ][ _50 ]  = {0};
static float LAST25DAYS[  NROFSTOCKS ][ _25 ]  = {0};

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

void Algorithms::CleanAlgorithms()
{  
    for (int i = 0; i < NROFSTOCKS; ++i)
    {
        own_Stock[i]    = true;
        posDirection[i] = true;
        crash[i]        = false;

        oldMa200[i] = 0;
        oldMa50[i]  = 0;
        oldMa25[i]  = 0;

        lokMax[i]   = 0;
        lokMin[i]   = 0;

        for (int j = 0; j < 200; ++j)
        {
            ma200[ i ][ j ]     = 0;
            ma50[ i ][ j % 50 ] = 0;
            ma25[ i ][ j % 25 ] = 0;

            LAST200DAYS[ i ][ j ]     = 0;
            LAST50DAYS[ i ][ j % 50 ] = 0;
            LAST25DAYS[ i ][ j % 25 ] = 0;
        }
    }
}

float Algorithms::getNrOfYears()
{
    static int totalDays = 0;
    static float years = 0;
    //totalDays = noOwnCounter + ownCounter;
    totalDays = days;
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
    cout << "increaseFactor = " << increaseFactor << endl;
    cout << "Years = " << years << endl;

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
    float portfValue = 0;
    static float startPortfValue = 0;
    float portfIncrease = 0;
    static float stockIncreasePerYear = 0;
    static float portfIncreasePerYear = 0;
    CleanAlgorithms();

    days = 0;


    startPortfValue = portfolio_p->cash;
    cout << "startPortfValue = " << startPortfValue << endl;

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
        ++days;
        updateStockDate(stocks);

        portfValue = curPortfolioDay->portfolioValue;

        previousPortfolioDay=curPortfolioDay;
        curPortfolioDay=curPortfolioDay->next;
    }

    nrOfYears = getNrOfYears();

    //För vanliga aktien
    //totalIncreaseStock = lastStockValue/firstStockValue;
    //getIncreasePerYear(totalIncreaseFactor, nrOfYears);
    //stockIncreasePerYear = getIncreasePerYear(totalIncreaseStock, nrOfYears);


    //För aktien i samband med algoritm:
    portfIncrease = portfValue/startPortfValue;
    percentageOfOwnStockTime = getPercentageOfOwnTime();
    
    //Används i samband med att det  bara finns en aktie i portföljen
    //portfIncreasePerYear = getIncreasePerYear(portfIncrease, percentageOfOwnStockTime*nrOfYears);
    portfIncreasePerYear = getIncreasePerYear(portfIncrease, nrOfYears);

    //cout << " stockIncreasePerYear = " << stockIncreasePerYear << endl;
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
    if(days % RECALIBRATE == 0)
    {
        TimeToRecalibrate = true;
    }

    if(TimeToRecalibrate)
    {
        RecalibratePortfolio(portfolio_p,curPortfolioDay,stocks);

    }
}

bool Algorithms::SellStock(Stock *stock, int nStock)
{
    //float ma200   = stock->head->ma200;
    //float ma50   = stock->head->ma50;
    float delta200   = stock->head->delta200;
    float closeValue = stock->head->close;
    float estStock   = stock->head->ma300;



    
    LAST200DAYS[nStock][sellStockCounter % _200] = closeValue;
    ma200[ nStock ][sellStockCounter % _200] = 0;

    LAST50DAYS[nStock][sellStockCounter % _50] = closeValue;
    ma50[ nStock ][sellStockCounter % _50] = 0;

    LAST25DAYS[nStock][sellStockCounter % _25] = closeValue;
    ma25[ nStock ][sellStockCounter % _25] = 0;
    
/*
    static bool initialStockValue = true;

    if (initialStockValue == true)
    {
        firstStockValue = closeValue;
        initialStockValue = false;
    }
    lastStockValue = closeValue;
*/

    //Calculate ma25[ nStock ]
    for (int i = 0; i < _25; ++i)
    {
        ma25[ nStock ][sellStockCounter % _25] = 
          ma25[ nStock ][sellStockCounter % _25] + (float) LAST25DAYS[nStock][i]/_25;
    }


    //Calculate ma50
    for (int i = 0; i < _50; ++i)
    {
        ma50[ nStock ][sellStockCounter % _50] = 
          ma50[ nStock ][sellStockCounter % _50] + (float) LAST50DAYS[nStock][i]/_50;
    }


    //Calculate ma200
    for (int i = 0; i < _200; ++i)
    {
        ma200[ nStock ][sellStockCounter % _200] = 
          ma200[ nStock ][sellStockCounter % _200] + (float) LAST200DAYS[nStock][i]/_200;
    }
    

    //MAX Value,
    if ((oldMa200[nStock] > ma200[ nStock ][sellStockCounter % _200]) && 
        posDirection[ nStock ])
        
    {
        lokMax[ nStock ] = ma200[ nStock ][sellStockCounter % _200];
        posDirection[ nStock ] = false;
    }


    //MIN Value
    if ((oldMa200[nStock] < ma200[ nStock ][sellStockCounter % _200]) && 
        (!posDirection[ nStock ]))
    {
        lokMin[ nStock ] = ma200[ nStock ][sellStockCounter % _200];
        posDirection[ nStock ] = true;
    }

    if ((1.2*ma200[ nStock ][sellStockCounter % _200] < lokMax[ nStock ]) && 
        (posDirection[ nStock ] == false))
    {
        crash[ nStock ] = true;
    }

    if (crash[ nStock ] == false)
    {


        bool SELL = (own_Stock[ nStock ] == true &&
                     closeValue < estStock*0.95);



        bool BUY = (own_Stock[ nStock ] == false &&
                    ma200[ nStock ][sellStockCounter % _200] > 1.04*lokMin[ nStock ] && 
                    closeValue > estStock);



        //SELL
        if (SELL)
        {
            own_Stock[ nStock ] = false;
        }

        //BUY
        if (BUY)
        {
            own_Stock[ nStock ] = true;
        }
    }

    else
    {
        if(ma200[ nStock ][sellStockCounter % _200] > estStock)
        {
            crash[ nStock ] = false;
        }
        

       //BUY
       if (own_Stock[ nStock ] == false &&
           oldMa50[nStock] < ma50[ nStock ][sellStockCounter % _50])
       {
            own_Stock[ nStock ] = true;
       }

       //SELL
       if (own_Stock[ nStock ] == true &&
           oldMa200[nStock] > ma200[ nStock ][sellStockCounter % _200] &&
           oldMa50[nStock] > ma50[ nStock ][sellStockCounter % _50] &&
           oldMa25[nStock] > ma25[ nStock ][sellStockCounter % _25])
       {
            own_Stock[ nStock ] = false;
       }


    }


    oldMa200[nStock] = ma200[ nStock ][sellStockCounter % _200];
    oldMa50[nStock]  = ma50[ nStock ][sellStockCounter % _50];
    oldMa25[nStock]  = ma25[ nStock ][sellStockCounter % _25];

    if (own_Stock[ nStock ])
    {   
        ++ownCounter;

    }
    else 
    {
        ++noOwnCounter;
    }

    
    return !own_Stock[ nStock ];


}

void Algorithms::BeatIndex(Portfolio *portfolio_p, 
                           Portfolio::portfolionode *curPortfolioDay, 
                           Stock stocks[]) 
{

    static bool buyStock[NROFSTOCKS] = {false};

    float moneyForEachStock = 0;
    int   nrOfStocksToBuy   = 0;
    float moneyToBuyWith    = 0;


    //RECALIBRATE is defined in algorithms.h
    if (days % RECALIBRATE != 0)
    {
        return;
    }

    Sell_All(portfolio_p, curPortfolioDay, stocks);
    
    moneyToBuyWith = portfolio_p->cash;

    //Chose which stocks to buy
    for (int i = 0; i < NROFSTOCKS; ++i)
    {        

        if (stocks[i].head->exist == false)
        {
            continue;
        }

        if (SellStock(&stocks[i], i))
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
    ++sellStockCounter;

    //Nothing to buy
    if (nrOfStocksToBuy == 0)
    {
        return;   
    }

    moneyForEachStock = moneyToBuyWith/nrOfStocksToBuy;

    for (int i = 0; i < NROFSTOCKS; ++i)
    {
        Stock::dayInfo *curStock  = stocks[i].head;

        string         stockName  = stocks[i].name;
        float          stockValue = curStock->close;


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