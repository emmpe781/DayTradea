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
	 else cout << "Unable to open file";
}

void ReadFile::ExtractDayData(string line,Stock& stock)
{
	int startvalue = 0;
	int endvalue= 0;
	string dayData("");
	for ( int i=0; i<10000; i++ ) {
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
	string close="";
	string low="";
	string volume="";

    bool first = true;
    bool last = false;

	for ( int i=0; i<10000; i++ ) {

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

			if (currlatest == "Volume") {volume=curr;}
			if (currlatest == "Symbol") {stock.name = curr;}
			if (currlatest == "Low") {low = curr;}
			if (currlatest == "Date") {date = curr;}
			if (currlatest == "Close") {close = curr;}

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
	stock.add_node(date,close,low,volume);
}

ReadFile::~ReadFile()
{
}

