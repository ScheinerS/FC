#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
import os
import matplotlib.pyplot as plt
from matplotlib import rcParams, cycler
#import csv
import numpy as np


path = os.path.dirname(os.path.realpath('__file__'))
sys.path.append(path)

TitleSize = 15
AxisLabelSize = 15
LegendSize = 12
NumberSize = 12

plt.close('all')

if os.name == 'posix':
    Linux = True

plt.rc('text', usetex=Linux)
plt.rc('font', family='serif')

# Para una transición suave de colores entre las curvas:
N=5    # cantidad de curvas
cmap = plt.cm.plasma #coolwarm, viridis, plasma, inferno, magma, cividis
rcParams['axes.prop_cycle'] = cycler(color=cmap(np.linspace(0, 1, N)))

#%%
paso = np.linspace(0, 30000, 100)
J = [0.1, 0.2, 0.3, 0.4]

corr = {}
corr[0.1] = np.exp(-paso/5e2)
corr[0.2] = np.exp(-paso/1e3)
corr[0.3] = np.exp(-paso/5e3)
corr[0.4] = np.exp(-paso/1e5)

#%%
# Gráfico de correlacion:

plt.figure()
for j in J:
    print('j = ',j)
    x = paso
    y = corr[j]
    plt.plot(x, y, 'o', label=r'$J = %g$'%j)

plt.xlabel(r'Paso', fontsize=AxisLabelSize)
plt.ylabel(r'Correlaci\'on', fontsize=AxisLabelSize)
plt.title(r'', fontsize=TitleSize)

plt.legend(loc='best', fontsize=LegendSize)
plt.grid(axis='both', color='k', linestyle='dashed', linewidth=2, alpha=0.2)
plt.show()
plt.savefig('Correlacion.png')

