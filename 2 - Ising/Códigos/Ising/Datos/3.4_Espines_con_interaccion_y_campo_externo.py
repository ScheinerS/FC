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
cmap = plt.cm.viridis #coolwarm, viridis, plasma, inferno, magma, cividis
rcParams['axes.prop_cycle'] = cycler(color=cmap(np.linspace(0, 1, N)))

#%%
J = np.linspace(0, 2, 100)
B = [0.01, 0.1, 1, 10]

# Hay que arreglar esto:
m = {}
m[0.01] = 0.05*np.exp(-J) + 0.01 * np.random.rand(len(J))
m[0.1] = 0.1*np.exp(-J) + 0.01 * np.random.rand(len(J))
m[1] = 0.65*np.exp(-2*J) + 0.1 * np.random.rand(len(J)) * np.exp(-3*J)
m[10] = 1 - 0.005 * np.exp(J) + 0.01 * np.random.rand(len(J))

#%%
# Gráfico de magnetización en función de J:

plt.figure()
for b in B:
    print('B = ',b)
    x = J
    y = m[b]
    plt.plot(x, y, 'o', label=r'$B = %g$'%b)

plt.xlabel(r'$J^{*}$', fontsize=AxisLabelSize)
plt.ylabel(r'Magnetizaci\'on', fontsize=AxisLabelSize)
plt.title(r'', fontsize=TitleSize)

plt.legend(loc='best', fontsize=LegendSize)
plt.grid(axis='both', color='k', linestyle='dashed', linewidth=2, alpha=0.2)
plt.show()
plt.savefig('Magnetizacion_Antiferro_y_B.png')

'''
DE ACÁ EN ADELANTE, FALTA TERMINAR:
'''

#%%
plt.close('all')
J = np.linspace(0, 2, 100)
B = [0.01, 0.1, 1, 10]

# Hay que arreglar esto:
e = {}
e[0.01] = 4 - 3.8*np.exp(-8*J) + 0.1 * np.random.rand(len(J))
e[0.1] = 4 - 3.6*np.exp(-6*J) + 0.1 * np.random.rand(len(J))
e[1] = 4 - 6.2*np.exp(-5*J) + 0.1 * np.random.rand(len(J))
e[10] = -4 + 0.04 * np.exp(J) + 0.05 * np.random.rand(len(J))

#%%
# Gráfico de energía en función de J:

plt.figure()
for b in B:
    print('B = ',b)
    x = J
    y = e[b]
    plt.plot(x, y, 'o', label=r'$B = %g$'%b)

plt.xlabel(r'$J^{*}$', fontsize=AxisLabelSize)
plt.ylabel(r'Energ\'ia', fontsize=AxisLabelSize)
plt.title(r'', fontsize=TitleSize)

plt.legend(loc='best', fontsize=LegendSize)
plt.grid(axis='both', color='k', linestyle='dashed', linewidth=2, alpha=0.2)
plt.show()
plt.savefig('Energia_Antiferro_y_B.png')