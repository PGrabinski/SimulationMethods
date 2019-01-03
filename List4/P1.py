import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

'''
Plots the distribution of generated random numbers
along with the theoretical probability density function
f(x)= 1/2 cos(x)
'''
results = pd.read_csv('R1/R1.dat')

x = np.arange(-np.pi/2, np.pi/2, 0.01)
values = 0.5 * np.cos(x)

results.Theta.plot.hist(bins=40, density=True)
plt.plot(x, values)

plt.show()
