import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

'''
Plots distribution of the random numbers generated from the Poisson distribution.
'''

results = pd.read_csv('R3/R3L5.csv')

bins = results.X.value_counts()/ len(results.X)
plt.scatter([i for i in range(0,len(bins.index))], bins.sort_index().values)
plt.xticks(range(0,len(bins.index)))
plt.show()