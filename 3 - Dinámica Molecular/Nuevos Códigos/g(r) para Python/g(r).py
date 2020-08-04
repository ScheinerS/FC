#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Aug  4 11:39:31 2020

@author: ramiro
"""

import os
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rcParams, cycler

plt.close('all')

if os.name == 'posix':
    Linux = True

plt.rc('text', usetex=Linux)
plt.rc('font', family='serif')

TitleSize = 15
AxisLabelSize = 15
LegendSize = 12

T_y_rho = [[0.3, 0.36], [0.3, 0.46], [0.3, 0.58], [0.3, 0.75], [0.3, 0.90], [0.3, 1],[1.5, 0.36], [1.5, 0.46], [1.5, 0.58], [1.5, 0.75], [1.5, 0.90], [1.5, 1]]


# Para una transición suave de colores entre las curvas:
N_curvas = len(T_y_rho)    # cantidad de curvas
cmap = plt.cm.Accent #coolwarm, viridis, plasma, inferno, magma, cividis
rcParams['axes.prop_cycle'] = cycler(color=cmap(np.linspace(0, 1, N_curvas)))
# help(plt.cm)

plt.figure()

for t_r in T_y_rho:
    T      = t_r[0]
    r      = t_r[1]
    
    data = np.loadtxt('g(r)(N=1000,t=%g,rho=%g).dat'%(T,r), skiprows=0, delimiter=' ', unpack=False)

    #plt.plot(Temp, Pres, label=r'$\rho = %g$'%r)

    r    = data[:, 0]
    g_r  = data[:, 1]

    plt.plot(r, g_r, label=r'$T = %g;\;\rho = %g$'%(T,r))

#plt.xlabel(r'Iteración', fontsize=AxisLabelSize)
#plt.ylabel(r'Desplazamiento Cuadrático', fontsize=AxisLabelSize)
plt.title(r'', fontsize=TitleSize)

plt.legend(loc='best', fontsize=LegendSize)
plt.grid(axis='both', color='k', linestyle='dashed', linewidth=2, alpha=0.2)
plt.show()

#plt.savefig('Gráficos/g(r).png')