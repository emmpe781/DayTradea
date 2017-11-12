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
import time
import csv
#import pythonToCpp as ToCpp
server = flask.Flask('stock-tickers')
server.secret_key = os.environ.get('secret_key', 'secret')
tickerList = []
count=0

df_symbol = pd.read_csv('tickers.csv')

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
            html.Button('Plot', id='myButton'),
            html.Div(id='out'),
            html.Div(id='tickerList'),
        ]), 
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
        events=[Event('myButton', 'click')],)
    def plotButton():
        f = open("Buttonpushed.txt", "a")
        f.write("PUSHED"+ "\n")
        f.close()
        return("PUSHED")

def start():
    app = dash.Dash()
    init_layout(app)
    callbacks(app)
    app.run_server(threaded=True)

def start2():
    print("HEEEJ")
    

def main():
    start()
    #threading.Thread(target=start).start()
    print("PASSED THREAD")
