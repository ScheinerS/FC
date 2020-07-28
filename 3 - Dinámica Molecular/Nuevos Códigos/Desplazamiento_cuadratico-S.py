#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Jul 23 10:08:52 2020

@author: ramiro
"""

import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rcParams, cycler

plt.close('all')

TitleSize = 15
AxisLabelSize = 15
LegendSize = 12

<<<<<<< HEAD
T_y_rho = [[0.8, 0.9], [1.4, 0.75], [1.5, 0.1], [1, 0.9]]

=======
rho = [1.4, 0.9, 1.4, 0.9, 0.1]
T   = [0.4, 0.8, 0.8, 1, 1.5]
>>>>>>> 2da2591ef3430f0af46a873d41b6b07c2f59c1b5
# Para una transición suave de colores entre las curvas:
N_curvas = 4    # cantidad de curvas
cmap = plt.cm.Accent #coolwarm, viridis, plasma, inferno, magma, cividis
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

plt.xlabel(r'Iteración', fontsize=AxisLabelSize)
plt.ylabel(r'Desplazamiento Cuadrático', fontsize=AxisLabelSize)
plt.title(r'', fontsize=TitleSize)

plt.legend(loc='best', fontsize=LegendSize)
plt.grid(axis='both', color='k', linestyle='dashed', linewidth=2, alpha=0.2)
plt.show()

plt.savefig('Gráficos/DCM.png')