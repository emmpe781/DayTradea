
def plotStdVectors(*arg):
    import plotly
    import plotly.plotly as py
    import plotly.graph_objs as go 
    plotly.offline.init_notebook_mode()
    import numpy as np
    from datetime import datetime
    attrList=[]
    
    time=arg[0][0]
    stock_close=arg[0][1]
    stock_mean=arg[1][1]
 
    close = np.fromiter(stock_close, dtype = np.float)
    mean = np.fromiter(stock_mean, dtype = np.float)

    
    for i in range(0,len(time)):
        date = datetime.strptime(time[i],'%Y-%m-%d')
        attrList.append(date)
    
    # Create a trace
    trace1 = go.Scatter(
        x = attrList,
        y = stock_close,
        name="close"   
    )
    trace2 = go.Scatter(
        x = attrList,
        y = stock_mean,
        name="mean"
    )
    
    plotdata = [trace1,trace2]
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

