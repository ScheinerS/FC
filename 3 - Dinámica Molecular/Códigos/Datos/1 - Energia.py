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
N=4    # cantidad de curvas
cmap = plt.cm.viridis #coolwarm, viridis, plasma, inferno, magma, cividis
rcParams['axes.prop_cycle'] = cycler(color=cmap(np.linspace(0, 1, N)))

#%%
# Lectura de los datos:

N = [512] #[32, 512]    # Cantidad de partículas.
Temperaturas = np.linspace(0.4,2.9,6) # Para hacer TODOS los gráficos: np.linspace(0.4, 49.9, 100)

for T in Temperaturas:
    data = pd.read_csv('Energias/energias(N=%d,T=%g)'%(N[0],T), delimiter=' ', skiprows=None)
    #data = np.loadtxt('energias(N=%d)'%(N), skiprows=1, delimiter=' ', unpack=True)
    #data = data.dropna()

    H = data.columns.values.tolist()


    plt.figure()
    for e in H[1:-1]:#['E_c', 'Vs','']:
        #print('N = ',n)
        x = data['paso']
        y = data[e]
        plt.plot(x, y, '.', label=r'$%s$'%e)
    
    plt.xlabel(r'Tiempo', fontsize=AxisLabelSize)
    plt.ylabel(r'Energ\'ia', fontsize=AxisLabelSize)
    plt.title(r'', fontsize=TitleSize)
    
    plt.legend(loc='best', fontsize=LegendSize)
    plt.grid(axis='both', color='k', linestyle='dashed', linewidth=2, alpha=0.2)
    plt.show()
    plt.savefig('Gráficos/Energia[N=%d,T=%g].png'%(N[0],T))

#%%
# Gráfico de lambda:

N=9    # cantidad de curvas
cmap = plt.cm.hot #vidis #coolwarm, viridis, plasma, inferno, magma, cividis
rcParams['axes.prop_cycle'] = cycler(color=cmap(np.linspace(0, 1, N)))


N = [512] #[32, 512]    # Cantidad de partículas.
Temperaturas = np.linspace(0.4,2.9,6) # Para hacer TODOS los gráficos: np.linspace(0.4, 49.9, 100)

plt.figure()

for T in Temperaturas:
    data = pd.read_csv('Energias/energias(N=%d,T=%g)'%(N[0],T), delimiter=' ', skiprows=None)
    
    x = data['paso']
    y = data['lambda_t']
    plt.plot(x, y, '.', label=r'$T = %g$'%T)
    
plt.xlabel(r'Tiempo', fontsize=AxisLabelSize)
plt.ylabel(r'Energ\'ia', fontsize=AxisLabelSize)
plt.title(r'', fontsize=TitleSize)

plt.legend(loc='best', fontsize=LegendSize)
plt.grid(axis='both', color='k', linestyle='dashed', linewidth=2, alpha=0.2)
plt.show()
plt.savefig('Gráficos/Lambda[N=%d].png'%(N[0]))

#%%
# Gráfico de valores medios y fluctuaciones de la energía:

N=3    # cantidad de curvas
cmap = plt.cm.winter_r #vidis #coolwarm, viridis, plasma, inferno, magma, cividis
rcParams['axes.prop_cycle'] = cycler(color=cmap(np.linspace(0, 1, N)))

N = [512] #[32, 512]    # Cantidad de partículas.

#Temperaturas = np.linspace(0.4,2.9,6)
# Para hacer TODOS los gráficos:
Temperaturas = np.linspace(0.4, 49.9, 100)

Vs_std = np.zeros(len(Temperaturas))
E_c_std = np.zeros(len(Temperaturas))
E_tot_std = np.zeros(len(Temperaturas))

Vs_mean = np.zeros(len(Temperaturas))
E_c_mean = np.zeros(len(Temperaturas))
E_tot_mean = np.zeros(len(Temperaturas))

for i in range(len(Temperaturas)):
    T = float(Temperaturas[i])
    data = pd.read_csv('Energias/energias(N=%d,T=%g)'%(N[0],T), delimiter=' ', skiprows=None)
    
    # Fluctuaciones:
    Vs_std[i] = np.std(data['Vs'])
    E_c_std[i] = np.std(data['E_c'])
    E_tot_std[i] = np.std(data['Vs+E_c'])
    
    # Valores medios:
    Vs_mean[i] = np.mean(data['Vs'])
    E_c_mean[i] = np.mean(data['E_c'])
    E_tot_mean[i] = np.mean(data['Vs+E_c'])


# Gráfico de fluctuaciones:

plt.figure()

plt.plot(Temperaturas, Vs_std, 'o', label=r'$Vs$')
plt.plot(Temperaturas, E_c_std, '.', label=r'$E_c$')
plt.plot(Temperaturas, E_tot_std, 'o', label=r'$Vs+E_c$')

plt.xlabel(r'Temperatura de equilibrio', fontsize=AxisLabelSize)
plt.ylabel(r'Fluctuacion en la energ\'ia', fontsize=AxisLabelSize)
plt.title(r'', fontsize=TitleSize)

plt.legend(loc='best', fontsize=LegendSize)
plt.grid(axis='both', color='k', linestyle='dashed', linewidth=2, alpha=0.2)
plt.show()
plt.savefig('Gráficos/Fluctuaciones[N=%d].png'%(N[0]))


# Gráfico de los valores medios:

N=3    # cantidad de curvas
cmap = plt.cm.winter #vidis #coolwarm, viridis, plasma, inferno, magma, cividis
rcParams['axes.prop_cycle'] = cycler(color=cmap(np.linspace(0, 1, N)))


plt.figure()

plt.plot(Temperaturas, Vs_mean, 'o', label=r'$Vs$')
plt.plot(Temperaturas, E_c_mean, 'o', label=r'$E_c$')
plt.plot(Temperaturas, E_tot_mean, 'o', label=r'$Vs+E_c$')

plt.xlabel(r'Temperatura de equilibrio', fontsize=AxisLabelSize)
plt.ylabel(r'Energ\'ia media', fontsize=AxisLabelSize)
plt.title(r'', fontsize=TitleSize)

plt.legend(loc='best', fontsize=LegendSize)
plt.grid(axis='both', color='k', linestyle='dashed', linewidth=2, alpha=0.2)
plt.show()
plt.savefig('Gráficos/Valores_medios[N=%d].png'%(N[0]))