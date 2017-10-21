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


with open('SE0000337842-1986-10-01-2017-10-18.csv', 'rt') as csvfile:
    spamreader = csv.reader(csvfile, delimiter=';')
    fieldnames = ['Open', 'Close','Volume','Low','High','Adj_Close','Date','Symbol']
    first=True
    temp=[]
    for row in spamreader:
        if first:
	        DateIndex=row.index('Date') 
	        HighIndex=row.index('High price')    
	        LowIndex=row.index('Low price')    
	        CloseIndex=row.index('Closing price')    
	        AverageIndex=row.index('Average price')    
	        VolumeIndex=row.index('Total volume')    
	        TurnoverIndex=row.index('Turnover')  
	        TradesIndex=row.index('Trades')   
	        first=False
        else:
            temp.append({'High': row[HighIndex], 'Date': row[DateIndex], 'Symbol': 'OMX30','Close': row[CloseIndex],'Low': row[LowIndex], 'Open': '1', 'Adj_Close': '1','Volume': row[VolumeIndex],})

f = open('stockdata_'+'OMX30'+'_'+'1986-10-01'+'_'+'2017-10-18'+'.dat', 'w')                   
simplejson.dump(temp, f)
f.close()

stockDataReversed=[]  
Temp=[] 
stockDataTemp=[]
stockData=simplejson.load(open('stockdata_OMX30_1986-10-01_2017-10-18.dat','r'))
for i in reversed(stockData):
    stockDataReversed.append(i)

d=datetime.strptime(stockDataReversed[0]['Date'],'%Y-%m-%d')
dend=datetime.strptime('2017-10-18','%Y-%m-%d')
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

f = open('stockdata_OMX30_1986-10-01_2017-10-18_fill.dat', 'w')                   

simplejson.dump(stockDataTemp, f)
f.close()