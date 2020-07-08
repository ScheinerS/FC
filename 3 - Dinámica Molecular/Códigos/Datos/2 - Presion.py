#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
import os
import matplotlib.pyplot as plt
from matplotlib import rcParams, cycler
#import csv
import numpy as np
import pandas as pd

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
N_curvas = 5    # cantidad de curvas
cmap = plt.cm.plasma #coolwarm, viridis, plasma, inferno, magma, cividis
rcParams['axes.prop_cycle'] = cycler(color=cmap(np.linspace(0, 1, N_curvas)))


# Lectura de los datos:

N = [512] # [125, 512]    # Cantidad de partículas.
L = 5

Lados = [5.4, 6.1, 6.3]#, 7.0]
# Para ver todos:
#Lados = np.linspace(5,7,21)
Temperaturas = np.linspace(0.4,1.9,16)

#%%

# Gráfico de energía media:

plt.figure()

for L in Lados:
    rho = N[0]/L**3
    
    E_tot_mean = np.zeros(len(Temperaturas))
    for i in range(len(Temperaturas)):
        T = float(Temperaturas[i])
        data = pd.read_csv('Presion/presiones(N=%d,L=%g,T=%g)'%(N[0],L,T), delimiter=' ', skiprows=None)
        
        E_tot_mean[i] = np.mean(data['Vs+E_c'])

        
        #data.columns = ['a', 'b']
        #data = data.reset_index()
        #data = data.drop('index', 1)
        
        #H = data.columns.values.tolist()
        
    plt.plot(Temperaturas, E_tot_mean, 'o', label=r'$L=%g, \rho = %.2f$'%(L,rho))


plt.xlabel(r'Temperatura', fontsize=AxisLabelSize)
plt.ylabel(r'Energ\'ia media', fontsize=AxisLabelSize)
plt.title(r'', fontsize=TitleSize)

plt.legend(loc='best', fontsize=LegendSize)
plt.grid(axis='both', color='k', linestyle='dashed', linewidth=2, alpha=0.2)
plt.show()
plt.savefig('Gráficos/Energia_media[N=%d,T=%g,rho=%g].png'%(N[0],T,rho))

#%%

# Gráfico de presión:

plt.figure()

for L in Lados:
    rho = N[0]/L**3
    
    p = np.zeros(len(Temperaturas))
    for i in range(len(Temperaturas)):
        T = float(Temperaturas[i])
        data = pd.read_csv('Presion/presiones(N=%d,L=%g,T=%g)'%(N[0],L,T), delimiter=' ', skiprows=None)
        
        p[i] = np.mean(data['p'])

        
        #data.columns = ['a', 'b']
        #data = data.reset_index()
        #data = data.drop('index', 1)
        
        #H = data.columns.values.tolist()
        
    plt.plot(Temperaturas, p, 'o', label=r'$L=%g, \rho = %.2f$'%(L,rho))


plt.xlabel(r'Temperatura', fontsize=AxisLabelSize)
plt.ylabel(r'Presi\'on', fontsize=AxisLabelSize)
plt.title(r'', fontsize=TitleSize)

plt.legend(loc='best', fontsize=LegendSize)
plt.grid(axis='both', color='k', linestyle='dashed', linewidth=2, alpha=0.2)
plt.show()
plt.savefig('Gráficos/Presion[N=%d,T=%g,rho=%g].png'%(N[0],T,rho))