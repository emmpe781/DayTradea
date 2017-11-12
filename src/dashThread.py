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

def bbands(price, window_size=10, num_of_std=5):
    rolling_mean = price.rolling(window=window_size).mean()
    rolling_std  = price.rolling(window=window_size).std()
    upper_band = rolling_mean + (rolling_std*num_of_std)
    lower_band = rolling_mean - (rolling_std*num_of_std)
    return rolling_mean, upper_band, lower_band

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
            value=['YHOO', 'GOOGL'],
            multi=True
        ),
        html.Div([
            html.Button('CreateData', id='createdatabutton'),
            html.Div(id='out'),
            html.Div(id='tickerList'),
        ]),
        html.Div([
            html.Button('Plot', id='plotbutton'),
            html.Div(id='out2'),
            html.Div(id='tickerList'),
        ]),  
        html.Div(id='graphs')
    ], className="container")


    external_css = ["https://fonts.googleapis.com/css?family=Product+Sans:400,400i,700,700i",
                    "https://cdn.rawgit.com/plotly/dash-app-stylesheets/2cc54b8c03f4126569a3440aae611bbef1d7a5dd/stylesheet.css"]

    for css in external_css:
        app.css.append_css({"external_url": css})

def callbacks(app):
    @app.callback(
        Output(component_id='tickerList',           component_property='children'),
        [Input(component_id='stockTickerInput',     component_property='value')])
    def updateTickers(tickers):
        tickerList = []
        for i, ticker in enumerate(tickers):
            tickerList.append(ticker)

    @app.callback(
        Output(component_id='out',      component_property='children'),
        events=[Event('createdatabutton', 'click')],)
    def CreateData():
        f = open("Buttonpushed.txt", "a")
        f.write("PUSHED"+ "\n")
        f.close()

    """@app.callback(
        dash.dependencies.Output('graphs','children'),
        [dash.dependencies.Input('stockTickerInput', 'value')])
    def update_graph(tickers):
        graphs = []
        for i, ticker in enumerate(tickers):
            try:
                df = DataReader(ticker, 'google',
                                dt.datetime(2017, 1, 1),
                                dt.datetime.now())
            except:
                graphs.append(html.H3(
                    'Data is not available for {}'.format(ticker),
                    style={'marginTop': 20, 'marginBottom': 20}
                ))
                continue

            candlestick = {
                'x': df.index,
                'open': df['Open'],
                'high': df['High'],
                'low': df['Low'],
                'close': df['Close'],
                'type': 'candlestick',
                'name': ticker,
                'legendgroup': ticker,
                'increasing': {'line': {'color': colorscale[0]}},
                'decreasing': {'line': {'color': colorscale[1]}}
            }
            graphs.append(dcc.Graph(
                id=ticker,
                figure={
                    'data': [candlestick],
                    'layout': {
                        'margin': {'b': 0, 'r': 10, 'l': 60, 't': 0},
                        'legend': {'x': 0}
                    }
                }
            ))
        #return graphs"""

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


        graph=dcc.Graph(id="PLOT",
                        figure={
                                'data': [trace],
                                'layout': {
                                    'margin': {'b': 0, 'r': 10, 'l': 60, 't': 0},
                                    'legend': {'x': 0}
                                }
                            })
        return graph

      
def start():
    appendedgraphs = []
    app = dash.Dash()
    init_layout(app)
    callbacks(app)
    app.run_server(threaded=True)
   

def main():
    start()

