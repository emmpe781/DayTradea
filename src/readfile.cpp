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
	string line;

	ifstream myfile (fname.c_str());
	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
		{
			ExtractDayData(line,stock_p);
	    }
	    myfile.close();
	 }
	else cout << "Unable to open file"<<endl;
}

void ReadFile::ExtractDayData(string line,Stock *stock_p)
{
	int startvalue = 0;
	int endvalue= 0;
	string dayData("");
	int length = line.size();
	for ( int i=0; i<length; i++ ) {
		if (line[i]=='{')
		{
			startvalue = i+1;
		}
		if (line[i]=='}')
		{
			endvalue = i;
			for (int k=startvalue; k<endvalue;k++){
				dayData += line[k];
			}
			ExtractStockData(dayData,stock_p);
			dayData = "";

		}
	}
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
    			tmp->close = expectedValue;
			}
    	}
		tmp=tmp->next;
    }
}

//Approved by Sven
void ReadFile::Mean(string date,Stock *stock,Stock stockCpy,int days)
{
	float sumStockClose=0;
	float mean;
	int i = 0;
	Stock::node *stockMeanHead = stock->head;
	Stock::node *tmpTail = stockCpy.head;
	Stock::node *tmpHead = stockCpy.head;

	while(stockMeanHead!= NULL){
			if (i < days){
				sumStockClose = sumStockClose + (tmpHead->close);
				i++;
			}
			else {
				mean=sumStockClose/days;
				stockMeanHead->close=mean;
				tmpTail=tmpTail->next;
				sumStockClose=sumStockClose+(tmpHead->close)-(tmpTail->close);
			};
		tmpHead=tmpHead->next;
		stockMeanHead=stockMeanHead->next;
    }
}

//Approved by Sven
ReadFile::~ReadFile()
{}

