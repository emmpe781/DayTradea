#!/usr/bin/python

#import threading
import time

import dash
import dash_core_components as dcc
import dash_html_components as html
from dash.dependencies import State, Event, Input, Output
import numpy as np
import colorlover as cl
import datetime as dt
import flask
import os
import pandas as pd
from pandas_datareader.data import DataReader
import time
import plotly.plotly as py
import plotly.graph_objs as go
server = flask.Flask('stock-tickers')
server.secret_key = os.environ.get('secret_key', 'secret')
tickerList = []
count=0
colorscale = cl.scales['9']['qual']['Paired']

df_symbol = pd.read_csv('tickers.csv')
f = open("Buttonpushed.txt", "w")
f.close()

def init_layout(app):
    app.layout = html.Div([
        html.Div([
            html.H2('ImbaPortfolio',
                    style={'display': 'inline',
                           'float': 'left',
                           'font-size': '2.65em',
                           'margin-left': '7px',
                           'font-weight': 'bolder',
                           'font-family': 'Product Sans',
                           'color': "rgba(117, 117, 117, 0.95)",
                           'margin-top': '20px',
                           'margin-bottom': '0'
                           }),
            html.Div(id='0'),
        ]),        

        dcc.Dropdown(
            id='stockTickerInput',
            options=[{'label': s[0], 'value': s[1]}
                     for s in zip(df_symbol.Company, df_symbol.Symbol)],
            value=['OMXS30'],
            multi=True
        ),
        html.Div([
            html.Button('CreateData', id='createdatabutton'),
            html.Div(id='out'),
            html.Div(id='tickerout'),
        ]),
        html.Div([
            html.Button('Plot', id='plotbutton'),
            html.Div(id='out2'),
        ]),  
        html.Div(id='graphs')
    ], className="container")


    external_css = ["https://fonts.googleapis.com/css?family=Product+Sans:400,400i,700,700i",
                    "https://cdn.rawgit.com/plotly/dash-app-stylesheets/2cc54b8c03f4126569a3440aae611bbef1d7a5dd/stylesheet.css"]

    for css in external_css:
        app.css.append_css({"external_url": css})

def callbacks(app):
    @app.callback(
        Output(component_id='tickerout',           component_property='children'),
        [Input(component_id='stockTickerInput',     component_property='value')])
    def updateTickers(tickers):
        tickerList = []
        for i, ticker in enumerate(tickers):
            tickerList.append(str(ticker))
        f = open("Tickers.txt", "w")
        f.write(str(tickerList))
        f.close()        

    @app.callback(
        Output(component_id='out',      component_property='children'),
        events=[Event('createdatabutton', 'click')],)
    def CreateData():
        f = open("Buttonpushed.txt", "a")
        f.write("PUSHED"+ "\n")
        f.close()
        return "Calculates data in c++"

    @app.callback(
        Output(component_id='out2', component_property='children'),
        events=[Event('plotbutton', 'click')],)
    def plotButton():
        # Create random data with numpy
        import numpy as np

        N = 500
        random_x = np.linspace(0, 1, N)
        random_y = np.random.randn(N)

        # Create a trace
        trace = go.Scatter(
            x = random_x,
            y = random_y
        )

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

        graph=dcc.Graph(id="PLOT",
                        figure={
                                'data': [trace],
                                'layout': layout
                                }
                            )
        return graph

      
def start():
    appendedgraphs = []
    app = dash.Dash()
    init_layout(app)
    callbacks(app)
    app.run_server(threaded=True)
   

def main():
    start()

