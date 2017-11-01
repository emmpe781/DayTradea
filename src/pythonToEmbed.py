import sys, os
import plotly
import plotly.plotly as py
import plotly.graph_objs as go 
from plotly.graph_objs import *

sys.stdout = open(os.devnull, 'w')
plotly.offline.init_notebook_mode()
sys.stdout = sys.__stdout__

import numpy as np
from datetime import datetime
plotdata = []

import dash
import dash_core_components as dcc
import dash_html_components as html


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


def plotStdVectors(*arg):
    layout = go.Layout(
            autosize=True,
            height=500,
            font=dict(color='#CCCCCC'),
            titlefont=dict(color='#CCCCCC', size='14'),
            margin=dict(
                l=42,
                r=42,
                b=55,
                t=45
            ),
            legend=dict(font=dict(size=10), orientation='h'),
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

    app = dash.Dash()

    app.layout = html.Div(children=[
        html.H1(children='Imbaportfolio'),

        html.Div(children='''
            10 år till ekonomiskt oberoende
        '''),

        dcc.Graph(
            id='example-graph',
            figure=fig
        )
    ])
    app.css.append_css({"external_url": "https://codepen.io/chriddyp/pen/bWLwgP.css"})

    app.run_server(debug=True)