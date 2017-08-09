//#include "matplotlib-cpp-master/matplotlibcpp.h"
//namespace plt = matplotlibcpp;
#include <list>
#include <string>
#include <iostream>


using namespace std;


class Stock{
	public:
	  string name;
	  struct node{
		  string date;
		  string volume;
		  string low;
		  string close;
		  node *next;
		  node *previous;

	  };
		node *head,*tail;
		Stock()
			{
				head = NULL;
				tail = NULL;
			}
		void add_node(string date,string close,string low,string volume)
			{
				node *tmp = new node;
				tmp->date = date;
				tmp->close = close;
				tmp->low = low;
				tmp->volume=volume;
				tmp->next = NULL;

				if(head == NULL)
				{
					head = tmp;
					tail = tmp;
				}
				else
				{
					tail->next = tmp;
					tail = tail->next;
				}
			}
		void Print()
		{
            while(head!= NULL){
            cout<< "date: " << head->date;
            cout<< ", close: " <<  head->close;
            cout<< ", low: " <<  head->low;
            cout<< ", volume: " <<  head->volume<<endl;
            head=head->next;
           }

		}
};

class ReadFile
{
public:
	ReadFile();
	void Read(string,Stock&);
	void ExtractDayData(string,Stock&);
	void ExtractStockData(string,Stock&);
	//virtual ~ReadFile();
};


//#include "readfile.h"
//#include "stock.h"
//#include <list>
//#include <iostream>
#include <fstream>
//#include <string>
//using namespace std;

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

//ReadFile::~ReadFile()
//{
//}




int main() {

	Stock omx30;
	omx30.add_node("hej","da","hej","da");
	omx30.add_node("bajs","bajs","bajs","bajs");
    string fname="data/stockdata_OMX30_1986-09-30_2017-03-24.dat";
	omx30.Print();

    ReadFile a;
    a.Read(fname,omx30);
	omx30.Print();

	return 0;

}
