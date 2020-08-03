#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Jul 25 17:23:26 2020

@author: ramiro
"""
import os
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rcParams, cycler


if os.name == 'posix':
    Linux = True

plt.rc('text', usetex=Linux)
plt.rc('font', family='serif')

TitleSize = 15
AxisLabelSize = 15
LegendSize = 12

# Para una transición suave de colores entre las curvas:
N_curvas = 7    # cantidad de curvas
cmap = plt.cm.plasma #coolwarm, viridis, plasma, inferno, magma, cividis
rcParams['axes.prop_cycle'] = cycler(color=cmap(np.linspace(0, 1, N_curvas)))

rho = [0.36, 0.46, 0.58, 0.75, 0.9, 1]

plt.figure()

for r in rho:
    data = np.loadtxt('Barrido(T=0.1-2.5,rho=%g).dat'%r, skiprows=1, delimiter=' ', unpack=False)

    Ekin = data[:,0]
    Epot = data[:,1]
    Etot = data[:,2]
    Temp = data[:,3]
    Pres = data[:,4]
    a=len(Ekin)
    iteracion=np.linspace(1,a,a)
    

    plt.plot(Temp,Pres, label=r'$\rho = %g$'%r)

plt.xlabel(r'Temperatura', fontsize=AxisLabelSize)
#plt.ylabel(r'Presión', fontsize=AxisLabelSize)
plt.title(r'', fontsize=TitleSize)

plt.legend(loc='best', fontsize=LegendSize)
plt.grid(axis='both', color='k', linestyle='dashed', linewidth=2, alpha=0.2)
plt.show()

#plt.savefig('Gráficos/Presion.png')