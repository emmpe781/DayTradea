#include "getData.h"
#include <iostream>
using namespace std;




//struct GetData::initStockList
//{
//	return cout << "!!!volvo!!!" << endl;
//};



//int GetData::getHistoricalData()
//{
//	cout << "!!!Hello Worlleeeeeeelllld!!!" << endl;
//	int amount = 3;
//	return amount;
//}

//import simplejson
//from yahoo_finance import Currency, Share
//from datetime import datetime, timedelta
//import copy
//
//def initStockList():
//    startdate='1986-09-30'
//    enddate='2017-03-24'
//    stockDict = {
//    'volvo': {'stockName':'VOLV-B.ST','startDate':startdate,'endDate':enddate},
//    'yahoo': {'stockName':'YHOO','startDate':startdate,'endDate':enddate},
//    'autoliv': {'stockName':'ALV','startDate':startdate,'endDate':enddate},
//    'af': {'stockName':'AF-B.ST','startDate':startdate,'endDate':enddate},
//    'OMXS30': {'stockName':'OMX30','startDate':startdate,'endDate':enddate},
//    'XACT.ST': {'stockName':'XACT.ST','startDate':startdate,'endDate':enddate},
//    }
//    return stockDict
//
//def getHistoricalData(stockDict,createNew,fill):
//    stockDataReversed=[]
//    Temp=[]
//    stockDataTemp=[]
//    if createNew == True:
//        stock = Share(stockDict['stockName'])
//        stockData = stock.get_historical(stockDict['startDate'],stockDict['endDate'])
//        print(stockData)
//    else:
//        stockData=simplejson.load(open('stockdata_'+stockDict['stockName']+'_'+stockDict['startDate']+'_'+stockDict['endDate']+'.dat','r'))
//
//    if fill == True:
//        for i in reversed(stockData):
//            stockDataReversed.append(i)
//        print(stockDataReversed)
//        d=datetime.strptime(stockDataReversed[0]['Date'],'%Y-%m-%d')
//        dend=datetime.strptime(stockDict['endDate'],'%Y-%m-%d')
//        delta = timedelta(days=1)
//        k=0
//        while (d <= dend and k<len(stockDataReversed)):
//            if k!=0:
//                elempast=copy.copy(stockDataReversed[k-1])
//                elem=copy.copy(stockDataReversed[k])
//            else:
//                elem=copy.copy(stockDataReversed[k])
//
//            if str(d)[0:10] == elem['Date']:
//                stockDataTemp.append(elem)
//                stockDataTemp[-1]['Date']=str(d)[0:10]
//                k=k+1
//                d += delta
//
//            elif str(d)[0:10] > elem['Date']:
//                k=k+1
//
//            elif str(d)[0:10] < elem['Date']:
//                if elempast:
//                    stockDataTemp.append(elempast)
//                else:
//                    stockDataTemp.append(elem)
//                stockDataTemp[-1]['Date']=str(d)[0:10]
//                d += delta
//
//        print(stockDataTemp)
//        f = open('stockdata_'+stockDict['stockName']+'_'+stockDict['startDate']+'_'+stockDict['endDate']+'.dat', 'w')
//        simplejson.dump(stockDataTemp, f)
//        f.close()
//
//    f=simplejson.load(open('stockdata_'+stockDict['stockName']+'_'+stockDict['startDate']+'_'+stockDict['endDate']+'.dat','r'))
//    return f
