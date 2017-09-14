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

void ReadFile::Read(string fname,Stock& stock)
{
	string line;

	ifstream myfile (fname.c_str());
	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
		{
			ExtractDayData(line,stock);
	    }
	    myfile.close();
	 }
	else cout << "Unable to open file"<<endl;
}

void ReadFile::ExtractDayData(string line,Stock& stock)
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
			ExtractStockData(dayData,stock);
			dayData = "";

		}
	}
}

void ReadFile::ExtractStockData(string line, Stock& stock)
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

			if (currlatest == "Symbol") {stock.name = curr;}
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
	stock.add_node_to_end(date,close);
}

void ReadFile::ExpectedValue(string date,Stock& stock,float percentage)
{
	float expectedincrease;
	float expectedvalue;
	expectedincrease = (percentage/100)/365+1;
	cout << expectedincrease << endl;
	bool first = true;
	Stock::node *tmp = stock.head;
    while(tmp!= NULL){
    	if (tmp->date >= date){
    		if (first){
    			expectedvalue = tmp->close;
    			first = false;
    		}
    		else {
    			expectedvalue= expectedvalue*expectedincrease;
    			tmp->close = expectedvalue;
			};
    	}
		tmp=tmp->next;
    }
}

void ReadFile::Mean(string date,Stock& stock,Stock stockCpy,int days)
{
	float total=0;
	int i = 0;
	Stock::node *stockHead = stock.head;
	Stock::node *tmpTail = stockCpy.head;
	Stock::node *tmpHead = stockCpy.head;

	while(stockHead!= NULL){
			if (i < days){
				total = total + (tmpHead->close);
				i++;
			}
			else {
				stockHead->close=total/days;
				tmpTail=tmpTail->next;
				total=total+(tmpHead->close)-(tmpTail->close);
			};
		tmpHead=tmpHead->next;
		stockHead=stockHead->next;
    }
}

ReadFile::~ReadFile()
{
}

