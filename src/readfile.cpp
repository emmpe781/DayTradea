/*
 * ReadFile.cpp
 *
 *  Created on: 3 juni 2017
 *      Author: Otur1337
 */

#include "readfile.h"
#include "stock.h"
#include <list>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


ReadFile::ReadFile(void)
{
    cout << "Initiating readfile" << '\n';
}

void ReadFile::Read(string fname,Stock *stock_p,string startdate)
{
	string rawData;
	ifstream myfile (fname.c_str());
	if (myfile.is_open())
	{
		getline (myfile,rawData);
	    myfile.close();
		ExtractDayData(rawData,stock_p,startdate);
	 }
	else {
		cout << "Unable to open file"<<endl;
	}
}

void ReadFile::PopulateStock(Stock *stock_p)
{
	ExpectedValue(stock_p, 7.5);
	Mean(stock_p, 200);
	Mean(stock_p, 50);
	BearBull(stock_p);
	Normalized(stock_p);
}

void ReadFile::ExtractDayData(string rawData,Stock *stock_p,string startdate)
{
	int startValue = 0;
	int endValue= 0;
	string dayData("");
	int length = rawData.size();
	for (int i=0; i<length; i++) {
		if (rawData[i]=='{')
		{
			startValue = i+1;
		}
		if (rawData[i]=='}')
		{
			endValue = i;
			for (int k=startValue; k<endValue;k++){
				dayData += rawData[k];
			}
			ExtractStockData(dayData,stock_p,startdate);
			dayData = "";

		}
	}
}


void ReadFile::ExtractStockData(string line, Stock *stock,string startdate)
{
	int startvalue = 0;
	int endvalue = 0;
	string curr("");
	string currlatest("");
	string date="";
	string exist="";
	double close=0;

    bool first = true;
    bool last = false;

    int length = line.size();
	for ( int i=0; i<length; i++ ) {
		if (line[i]=='"' && first)
		{
			startvalue = ++i;
			first = false;
			last = false;
		}
		if (line[i]=='"' && last)
		{
			endvalue = i;
			for (int k=startvalue; k<endvalue;k++){
				curr += line[k];
			};

			if (currlatest == "Symbol") {stock->name = curr;}
			if (currlatest == "Date") {date = curr;}
			if (currlatest == "Close") {close = stof(curr);}
			if (currlatest == "Exist") {exist = curr;}
			currlatest=curr;
			curr = "";

			first = true;
			last = false;
		}
		if (first == false)
		{
		last = true;
		}
	}
	if (date >= startdate){
		stock->add_node_to_end(date,close,exist);
	}
}


//Approved by Sven
void ReadFile::ExpectedValue(Stock* stock,float percentage)
{
	float expectedIncrease;
	float expectedValue;
	expectedIncrease = (percentage/100)/365+1;
	Stock::dayInfo *tmp = stock->head;
	while(!tmp->exist){
    	tmp=tmp->next;
	}
	expectedValue = tmp->close;

    while(tmp!= NULL){
	    	//Rekalibrera estimering om index går MEGA BULL!
			if ((tmp->close - expectedValue) > expectedValue*1.4)
			{
				expectedValue = expectedValue*expectedIncrease + 
	    			(tmp->close - expectedValue)/2000;
			}
			//Rekalibrera estimering om index går MEGA BEAR!
			else if (tmp->close < 0.65*expectedValue)
			{
				expectedValue = tmp->close*1.4; 			
			}

	    	expectedValue = expectedValue*expectedIncrease;
	    	tmp->est = expectedValue;
    	
    	tmp=tmp->next;
    }
}



void ReadFile::BearBull(Stock* stock)
{
	Stock::dayInfo *stockHead = stock->head;
	float lastMa200 = 0;
	float lastMa50 = 0;
	float const diffValue = 0.00085f;
	static int lastBearBull = 0;
	static float const diffEst = 1.2;

	while(stockHead != NULL){
    	if (stockHead->exist){
			stockHead->bearBull = lastBearBull;
			if (stockHead->ma200 != 0)
			{

				//bull->bear
				if (((stockHead->ma200 - lastMa200) < -diffValue*lastMa200) && //Lutningen är tillräckligt negativ för ma200
					(stockHead->bearBull == 1800)   && //vi är i Bulltrend
					(stockHead->ma50 < lastMa50)    && //negativ lutning på ma50
					(stockHead->close > stockHead->est*diffEst)) //Aktiekursen ska vara större än estimerade värdet
					{
						stockHead->bearBull = BEAR;
					}

				//Bear->Bull
				if ((stockHead->ma50 > stockHead->ma200) &&
					((stockHead->ma200 - lastMa200) > lastMa200*diffValue/4) &&
					(stockHead->bearBull == 10)) //*diffEst)) //Använd BEAR macrot
				{
					stockHead->bearBull = BULL;
				}

				if (stockHead->bearBull == 0 && stockHead->ma200 >= lastMa200) // Före BEAR/BULL
				{
					stockHead->bearBull = BULL;
				}

			}
		}
		lastBearBull = stockHead->bearBull;
		lastMa200 = stockHead->ma200;
		lastMa50 = stockHead->ma50;
		stockHead=stockHead->next;
	}
}

//Approved by Sven
void ReadFile::Mean(Stock *stock,int days)
{
	float sumStockClose=0;
	float mean;
	int i = 0;
	Stock::dayInfo *stockTail = stock->head;
	Stock::dayInfo *stockHead = stock->head;

	while(stockHead!= NULL){
    	if (stockHead->exist){

			//fyll på ma 50/100/200
			if (i < days){
				sumStockClose = sumStockClose + (stockHead->close);
				//stockHead->ma200=stockHead->close;
				if(days==200){
					stockHead->ma200 = 0;
				}
				if(days==50){
					stockHead->ma50 = 0;
				}
				i++;
			}
			else {
				mean=sumStockClose/days;
				if(days==200){
					stockHead->ma200=mean;
				}
				if(days==50){
					stockHead->ma50 = mean;
				}	
				stockTail=stockTail->next;
				sumStockClose=sumStockClose+(stockHead->close)-(stockTail->close);
			};
			stockHead=stockHead->next;
		}
		else{
			stockTail=stockTail->next;
			stockHead=stockHead->next;
		}
    }
}


void ReadFile::Normalized(Stock *stock)
{
	Stock::dayInfo *first_day = stock->head;
	Stock::dayInfo *day = stock->head;

	while(day!= NULL){

		if (day->exist)
		{
			day->norm = day->close / first_day->close;
		}
		else
		{
			first_day=first_day->next;
		}
		day=day->next;
    }
}

void ReadFile::NormalizedPort(Portfolio *port)
{
	Portfolio::portfolionode *first_day = port->curPortfolio;
	Portfolio::portfolionode *day = port->curPortfolio;

	while(day!= NULL){
		day->normValue = day->portfolioValue / first_day->portfolioValue;
		day=day->next;
    }
}

//Approved by Sven
ReadFile::~ReadFile()
{}

