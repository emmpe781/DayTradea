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

        //Om "vi" är en av de två sämsta aktierna
        if(removeStocks > nrOfWorseStocks)
        {
            rankStock[i].buyStock = false;
            
            ++nrOfRemovedStocks;
        }
        nrOfWorseStocks = 0;

    }
    return nrOfRemovedStocks;
}

bool Algorithms::SellStock(Stock *stock, const bool ownStock)
{
    //float ma200   = stock->head->ma200;
    //float ma50   = stock->head->ma50;
    float delta200   = stock->head->delta200;
    float closeValue = stock->head->close;
    float estStock   = stock->head->ma300;

    static bool initialStockValue = true;

    if (initialStockValue == true)
    {
        firstStockValue = closeValue;
        initialStockValue = false;
    }
    lastStockValue = closeValue;




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

    const int _25 = 25;
    static float MA25[_25] = {closeValue};

    float sumMaDays = 0;
    static float ma200[_200] = {0};
    static float ma50[_50] = {0};
    static float ma25[_25] = {0};

    static float oldMa200 = 0;
    static float oldMa50 = 0;
    static float oldMa25 = 0;
    float oldMaDays = 0;
    
    MA200[counter % _200] = closeValue;
    ma200[counter % _200] = 0;

    MA50[counter % _50] = closeValue;
    ma50[counter % _50] = 0;

    MA25[counter % _25] = closeValue;
    ma25[counter % _25] = 0;
    

    oldMaDays = maDays[counter % days];

    
    //Calculate ma25
    for (int i = 0; i < _25; ++i)
    {
        ma25[counter % _25] = ma25[counter % _25] + (float) MA25[i]/_25;
    }


    //Calculate ma50
    for (int i = 0; i < _50; ++i)
    {
        ma50[counter % _50] = ma50[counter % _50] + (float) MA50[i]/_50;
    }



    //Calculate ma200
    for (int i = 0; i < _200; ++i)
    {
        ma200[counter % _200] = ma200[counter % _200] + (float) MA200[i]/_200;
    }


    deltaCloseMa50[counter % days] = closeValue - ma50[counter % _50];
    deltaMa50Ma200[counter % days] = ma50[counter % _50] - ma200[counter % _200];
    maDays[counter % days] = closeValue;

    for (int i = 0; i < days; ++i)
    {
        sumDiffCloseMa50 = sumDiffCloseMa50 + deltaCloseMa50[i];
        sumDiffMa50Ma200 = sumDiffMa50Ma200 + deltaMa50Ma200[i];
        sumMaDays = sumMaDays + maDays[i]/days;

    }
    ++counter;

    static int i = 0;
    bool sellStock = false;


    sellStock = false;
    
    
    static float lokMax = ma200[counter % _200];
    static bool posDirection = true;

    //MAX Value,
    if ((oldMa200 > ma200[counter % _200]) && posDirection)
        
    {
        lokMax = ma200[counter % _200];
        posDirection = false;
    }


    static float lokMin = ma200[counter % _200];

    //MIN Value
    if ((oldMa200 < ma200[counter % _200]) && (!posDirection))
    {
        lokMin = ma200[counter % _200];
        posDirection = true;
    }



    static bool crash = false;

    if ((1.2*ma200[counter % _200] < lokMax) && (posDirection == false))
    {
        crash = true;
    }

    if (crash == false)
    {


        bool SELL = (own_Stock == true &&
                      closeValue < estStock*0.95);



        bool BUY = (own_Stock == false &&
                      ma200[counter % _200] > 1.04*lokMin && 
                      closeValue > estStock);



        //SELL
        if (SELL)
        {
            own_Stock = false;
            sellStock = true;
        }

        //BUY
        if (BUY)
        {
            own_Stock = true;
            sellStock = false;
        }
    }

    else
    {
        if(ma200[counter % _200] > estStock)
        {
            crash = false;
        }
        

       //BUY
       if (own_Stock == false &&
           oldMa50 < ma50[counter % _50] &&
           oldMa25 < ma25[counter % _25])
       {
            own_Stock = true;
            sellStock = false;
       }

       //SELL
       if (own_Stock == true &&
           oldMa200 > ma200[counter % _200] &&
           oldMa50 > ma50[counter % _50] &&
           oldMa25 > ma25[counter % _25])
       {
            own_Stock = false;
            sellStock = true;
       }


    }


    oldMa200 = ma200[counter % _200];
    oldMa50  = ma50[counter % _50];
    oldMa25  = ma25[counter % _25];

    if (own_Stock)
    {   
        ++ownCounter;

    }
    else 
    {
        ++noOwnCounter;
    }

    //TEMP för att fixa köpa hela tiden -> index!!
    own_Stock = true;

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
        }
/*
        if (rankStock[i].buyStock == true)
        {
            cout << "buy stock " << endl;    
        }
        else 
        {
            cout << "DO not buy stock " << endl;       
        }*/
        
    }


    float moneyToBuyWith = portfolio_p->cash;

    if (nrOfStocksToBuy == 0)
    {
        nrOfStocksToBuy = 1;
    }

    float moneyForEachStock = moneyToBuyWith/nrOfStocksToBuy;

    cout << "moneyForEachStock = " << moneyForEachStock << endl;
    cout << "nrOfStocksToBuy = " << nrOfStocksToBuy << endl;

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
            cout << "Buy ncurrent stock = " << rankStock[i].stockName << endl;
            Portfolio::portfolionode *tmp = curPortfolioDay;
            portfolio_p->buy(stockValue, rankStock[i].stockName, 
                             moneyForEachStock, tmp);
        }

        
        
    }



}



Algorithms::~Algorithms() {
    // TODO Auto-generated destructor stub
}