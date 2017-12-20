"""import sys, os
import plotly
import plotly.plotly as py
import plotly.graph_objs as go 
from plotly.graph_objs import *

import numpy as np
from datetime import datetime
plotdata = []


def appendList(*arg):
    dateList=[]
    name=arg[0]
    time=arg[1] 
    value=arg[2]
    attr=arg[3]
 
    data = np.fromiter(value, dtype = np.float)
    
    for i in range(0,len(time)):
        date = datetime.strptime(time[i],'%Y-%m-%d')
        dateList.append(date)
    
    trace = go.Scatter(
        #legendgroup = name, # this can be any string, not just "group"
        x = dateList,
        y = data,
        name= name +" - " + attr  
    )

    plotdata.append(trace)

def appendListFill(*arg):
    dateList=[]
    name=arg[0]
    time=arg[1]
    valueLower=arg[2]
    valueUpper=arg[3]
    attr=arg[4]
 
    upper = np.fromiter(valueUpper, dtype = np.float)
    lower = np.fromiter(valueLower, dtype = np.float)

    for i in range(0,len(time)):
        date = datetime.strptime(time[i],'%Y-%m-%d')
        dateList.append(date)
    
    x_rev = dateList[::-1]
    valueLower = valueLower[::-1]

    print(lower[0:10])
    print(valueLower[0:10])

    trace = go.Scatter(
        x = dateList+x_rev,
        y = valueUpper+valueLower,
        fill='tozerox',
        fillcolor='rgba(0,100,80,0.2)',
        line=Line(color='transparent'),
        #showlegend=False,
        name='Bear/Bull',
    )

    plotdata.append(trace)

def returndata(*arg):
    return plotdata"""


def test():
    print("hej")