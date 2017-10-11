
import plotly
import plotly.plotly as py
import plotly.graph_objs as go 
plotly.offline.init_notebook_mode()
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

data = [trace]

plotly.offline.plot(data, filename='basic-line')