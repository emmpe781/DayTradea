import sys, os
import plotly
import plotly.plotly as py
import plotly.graph_objs as go 
sys.stdout = open(os.devnull, 'w')
plotly.offline.init_notebook_mode()
sys.stdout = sys.__stdout__

import numpy as np
from datetime import datetime
dateList=[]
plotdata = []

def appendList(*arg):
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


def plotStdVectors(*arg):
    layout = go.Layout(
            xaxis=dict(
                rangeselector=dict(
                buttons=list([
                    dict(count=1,
                        label='1m',
                        step='month',
                        stepmode='backward'),     
                    dict(count=6,
                        label='6m',
                        step='month',
                        stepmode='backward'),
                    dict(count=1,
                        label='YTD',
                        step='year',
                        stepmode='todate'),
                    dict(count=1,
                        label='1y',
                        step='year',
                        stepmode='backward'),
                    dict(step='all')
                ])
            ),
            #rangeslider=dict(),
            #type='date'
            ),
            yaxis=dict(
                type='log',
                autorange=True,
                showgrid=True,
                zeroline=True,
                showline=True,
                autotick=True,
        )           
    )
    fig = dict(data=plotdata, layout=layout)
    plotly.offline.plot(fig)

