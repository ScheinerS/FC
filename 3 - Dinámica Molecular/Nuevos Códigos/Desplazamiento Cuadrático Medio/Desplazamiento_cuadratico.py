#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Jul 23 10:08:52 2020

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

T_y_rho_Viejos = [[0.3, 0.36], [0.3, 0.46], [0.3, 0.58], [0.3, 0.75], [0.3, 0.9], [0.3, 1],[1.5, 0.36], [1.5, 0.46], [1.5, 0.58], [1.5, 0.75], [1.5, 0.9], [1.5, 1]]
T_y_rho = []

for i in [0, 5, 6, 11]:
    T_y_rho.append(T_y_rho_Viejos[i])

# Para una transición suave de colores entre las curvas:
N_curvas = len(T_y_rho)+1    # cantidad de curvas
cmap = plt.cm.plasma #coolwarm, viridis, plasma, inferno, magma, cividis
rcParams['axes.prop_cycle'] = cycler(color=cmap(np.linspace(0, 1, N_curvas)))
# help(plt.cm)

plt.figure()

for t_r in T_y_rho:
    T = t_r[0]
    r = t_r[1]
    data = np.loadtxt('DCM(T=%g,rho=%g).dat'%(T,r), skiprows=1, delimiter=' ', unpack=False)

    #plt.plot(Temp, Pres, label=r'$\rho = %g$'%r)

    iteracion = data[:, 0]
    DCM = data[:, 1]

    plt.plot(iteracion, DCM, label=r'$T = %g;\;\rho = %g$'%(T,r))

#plt.xlabel(r'Iteración', fontsize=AxisLabelSize)
#plt.ylabel(r'Desplazamiento Cuadrático', fontsize=AxisLabelSize)
plt.title(r'', fontsize=TitleSize)

plt.legend(loc='best', fontsize=LegendSize)
plt.grid(axis='both', color='k', linestyle='dashed', linewidth=2, alpha=0.2)
plt.show()

plt.savefig('DCM.png')