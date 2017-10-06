
def plotStdVectors(x,y):
    import plotly
    import plotly.plotly as py
    import plotly.graph_objs as go 
    plotly.offline.init_notebook_mode()
    import numpy as np
    from datetime import datetime
    attrList=[]
        
    #random_x = np.fromiter(x, dtype = np.string)
    random_y = np.fromiter(y, dtype = np.float)
    
    for i in range(0,len(x)):
        date = datetime.strptime(x[i],'%Y-%m-%d')
        attrList.append(date)

    # Create a trace
    trace = go.Scatter(
        x = attrList,
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
            rangeslider=dict(),
            type='date'
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

