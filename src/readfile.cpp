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

void ReadFile::Read(string fname,Stock *stock_p)
{
	string rawData;
	ifstream myfile (fname.c_str());
	if (myfile.is_open())
	{
		getline (myfile,rawData);
	    myfile.close();
		ExtractDayData(rawData,stock_p);
	 }
	else {
		cout << "Unable to open file"<<endl;
	}
}

void ReadFile::ExtractDayData(string rawData,Stock *stock_p)
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
			ExtractStockData(dayData,stock_p);
			dayData = "";

		}
	}
}

void nyfunction(){
}

void ReadFile::ExtractStockData(string line, Stock *stock)
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
	stock->add_node_to_end(date,close);
}


//Approved by Sven
void ReadFile::ExpectedValue(string date,Stock* stock,float percentage)
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
    			expectedValue= expectedValue*expectedIncrease;
    			tmp->est = expectedValue;
			}
    	}
		tmp=tmp->next;
    }
}

void ReadFile::BearBull()
{
	//Index eller Aktiekurs för varje datum
	//Läsa ut Ma200
	//Vill ha skillnaden på estimerade värdet och sanna värdet?


}

void ReadFile::ExpectedValue2(string date,Stock* stock,float percentage)
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
}


//Approved by Sven
void ReadFile::Mean(string date,Stock *stock,int days)
{
	float sumStockClose=0;
	float mean;
	int i = 0;
	Stock::node *stockTail = stock->head;
	Stock::node *stockHead = stock->head;

	while(stockHead!= NULL){
			if (i < days){
				sumStockClose = sumStockClose + (stockHead->close);
				stockHead->ma200=stockHead->close;
				i++;
			}
			else {
				mean=sumStockClose/days;
				stockHead->ma200=mean;
				stockTail=stockTail->next;
				sumStockClose=sumStockClose+(stockHead->close)-(stockTail->close);
			};
		stockHead=stockHead->next;
    }
}

//Approved by Sven
ReadFile::~ReadFile()
{}

