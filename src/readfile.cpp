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

			nyfunction(); //CLEAN UP
			for (int k=startValue; k<endValue;k++){
				dayData += rawData[k];
			}
			ExtractStockData(dayData,stock_p,startdate);
			dayData = "";

		}
	}
}

void nyfunction(){
}

void ReadFile::ExtractStockData(string line, Stock *stock,string startdate)
{
	int startvalue = 0;
	int endvalue = 0;
	string curr("");
	string currlatest("");
	string date="";
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
		stock->add_node_to_end(date,close);
	}
}


//Approved by Sven
void ReadFile::ExpectedValue(Stock* stock,float percentage)
{
	float expectedIncrease;
	float expectedValue;
	expectedIncrease = (percentage/100)/365+1;
	Stock::node *tmp = stock->firstStockDate;
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
	Stock::node *stockHead = stock->firstStockDate;
	float lastMa200 = 0;
	float lastMa50 = 0;
	float const diffValue = 0.00175f;
	static int lastBearBull = 0;

	while(stockHead != NULL){

		stockHead->bearBull = lastBearBull;
		if (stockHead->ma200 != 0)
		{

			//bull->bear
			if ((stockHead->ma200 < lastMa200) &&
				((stockHead->ma200 - lastMa200) < -diffValue*lastMa200) &&
				(stockHead->bearBull == 1800) &&
				(stockHead->ma50 < lastMa50)) //BULL macrot!

				{
					stockHead->bearBull = BEAR;
				}

			//Bull->bear
			if ((stockHead->ma50 > stockHead->ma200) &&
				((stockHead->ma200 - lastMa200) > lastMa200*diffValue/2) &&
				(stockHead->bearBull == 10)) //Använd BEAR macrot
			{
				stockHead->bearBull = BULL;
			}

			if (stockHead->bearBull == 0 && stockHead->ma200 >= lastMa200) // Före BEAR/BULL
			{
				stockHead->bearBull = BULL;
			}

		}
		lastBearBull = stockHead->bearBull;
		lastMa200 = stockHead->ma200;
		lastMa50 = stockHead->ma50;
		stockHead=stockHead->next;
	}
}

/*void ReadFile::ExpectedValue2(string date,Stock* stock,float percentage)
{
	float expectedIncrease;
	float expectedValue;
	expectedIncrease = (percentage/100)/365+1;
	bool first=true;
	Stock::node *tmp = stock->head;
    while(tmp!= NULL){
    	if (tmp->date >= date){
    		if (first){
    			//Set expectedValue to the value of our start date.
    			//Only done once.
    			expectedValue = tmp->close;
    			first=false;
    		}
    		else {
    			//Återkoppla skillnaden mellan omxs30 och vårt estimerade värde
    			//kalibrera om estimerade värdet ifall bear till bull,

    			expectedValue= expectedValue*expectedIncrease;
    			tmp->close = expectedValue;
			}
    	}
		tmp=tmp->next;
    }
}*/


//Approved by Sven
void ReadFile::Mean(Stock *stock,int days)
{
	float sumStockClose=0;
	float mean;
	int i = 0;
	Stock::node *stockTail = stock->firstStockDate;
	Stock::node *stockHead = stock->firstStockDate;

	while(stockHead!= NULL){

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
}

//Approved by Sven
ReadFile::~ReadFile()
{}

