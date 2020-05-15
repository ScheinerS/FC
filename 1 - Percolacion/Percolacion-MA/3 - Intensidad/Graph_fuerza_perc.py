import sys
import os
import matplotlib.pyplot as plt
from matplotlib import rcParams, cycler
import pandas as pd
import numpy as np
#from scipy.stats import chisquare

path = os.path.dirname(os.path.realpath('__file__'))
sys.path.append(path)

TitleSize = 20
AxisLabelSize = 20
LegendSize = 12
NumberSize = 12

plt.close('all')

if os.name == 'posix':
    Linux = True

plt.rc('text', usetex=Linux)
plt.rc('font', family='serif')

            
# Para una transición suave de colores entre las curvas:
N=7    # cantidad de curvas
cmap = plt.cm.inferno #coolwarm, viridis, plasma, inferno, magma, cividis
rcParams['axes.prop_cycle'] = cycler(color=cmap(np.linspace(0, 1, N)))

#%%

for i in range(2,8):
    L=2**i
    print(L)
    data = pd.read_csv('perc_' + str(L) + '.csv', header=None)
    data.columns = ['x', 'y']

    plt.plot(data['x'], data['y'],label='L=%d'%L,zorder=i)

#plt.figure()
plt.xlabel(r'Probabilidad', fontsize=AxisLabelSize)
plt.ylabel(r'Intensidad Cluster Percolante', fontsize=AxisLabelSize)

#plt.title(r'', fontsize=TitleSize)
plt.legend(loc='best', fontsize=LegendSize)
plt.grid(axis='both', color='k', linestyle='dashed', linewidth=2, alpha=0.2)
plt.show()

if Linux:
    plt.savefig("Intensidad_cluster_percolante.png")