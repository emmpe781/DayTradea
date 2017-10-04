
def plotStdVectors(x,y):
    import plotly
    import plotly.plotly as py
    import plotly.graph_objs as go 
    plotly.offline.init_notebook_mode()
    import numpy as np

    random_x = np.fromiter(x, dtype = np.float)
    random_y = np.fromiter(y, dtype = np.float)
    # Create a trace
    trace = go.Scatter(
        x = random_x,
        y = random_y
    )

    plotdata = [trace]
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

#plotStdVectors()