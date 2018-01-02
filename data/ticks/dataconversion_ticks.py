# -*- coding: utf-8 -*-
"""
Created on March 9 12:42:53 2016

@author: toll3
"""

import simplejson
import csv
import json as simplejson
#from yahoo_finance import Currency, Share
from datetime import datetime, timedelta
import copy

TICKS=['BURE','CRED-A','INDU-C','INVE-B','LATO-B','LUND-B','ORES','RATO-B','SVOL-B']

#TICK='BURE'
for TICK in TICKS:
    with open(TICK+'.csv', 'rt') as csvfile:
        spamreader = csv.reader(csvfile, delimiter=';')
        #fieldnames = ['Symbol','Adj_Close','High','Open', 'Close','Volume','Date','Low']
        fieldnames = ['Symbol','Close','Date']
        temp=[]
        i=0
        for row in spamreader:
            if i==1:
                DateIndex=row.index('Date') 
                HighIndex=row.index('High price')    
                LowIndex=row.index('Low price')    
                CloseIndex=row.index('Closing price')    
                AverageIndex=row.index('Average price')    
                VolumeIndex=row.index('Total volume')    
                TurnoverIndex=row.index('Turnover')  
                TradesIndex=row.index('Trades')   
            if (i>1):
                #temp.append({'Symbol': 'OMX30', 'Adj_Close': '1','High': row[HighIndex],'Open': '1','Close': row[CloseIndex],'Volume': "1",'Date': row[DateIndex], 'Low': row[LowIndex]})
                if (row[CloseIndex] == "0,00"):
                    close = closeprevious
                else:
                    close = row[CloseIndex]
                closeprevious = close
                temp.append({'Symbol': TICK, 'Close': close.replace(",","."),'Date': row[DateIndex]})
            i=i+1;

    f = open('stockdata_'+TICK+'.dat', 'w')                   
    simplejson.dump(temp, f)
    f.close()

    stockDataReversed=[]  
    Temp=[] 
    stockDataTemp=[]
    stockData=simplejson.load(open('stockdata_'+TICK+'.dat','r'))
    for i in reversed(stockData):
        stockDataReversed.append(i)

    d=datetime.strptime(stockDataReversed[0]['Date'],'%Y-%m-%d')
    dend=datetime.strptime('2017-12-28','%Y-%m-%d')
    delta = timedelta(days=1)
    k=0
    while (d <= dend and k<len(stockDataReversed)):
        if k!=0:
            elempast=copy.copy(stockDataReversed[k-1])
            elem=copy.copy(stockDataReversed[k])
        else:
            elem=copy.copy(stockDataReversed[k])

        if str(d)[0:10] == elem['Date']:
            stockDataTemp.append(elem)
            stockDataTemp[-1]['Date']=str(d)[0:10]
            k=k+1
            d += delta

        elif str(d)[0:10] > elem['Date']:         
            k=k+1

        elif str(d)[0:10] < elem['Date']:
            if elempast:
                stockDataTemp.append(elempast)
            else:
                stockDataTemp.append(elem)
            stockDataTemp[-1]['Date']=str(d)[0:10] 
            d += delta

    f1 = open('stockdata_'+TICK+'.dat', 'w')                   
    simplejson.dump(stockDataTemp, f1)
    f.close()