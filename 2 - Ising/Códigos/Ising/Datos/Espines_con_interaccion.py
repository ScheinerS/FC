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

#%%
# Gráfico de magnetización (L=32):
L=32
J = np.linspace(0, 0.6, 200)
m = 1 / (1 + np.exp(-50*(J-0.44)))

c = 0.8 # Amplitud del ruido.
noise = c * J * np.exp(-100*(J-0.4)**2) * np.random.rand(len(J))
H = np.heaviside(1-(m+noise), 0)
noise = noise*H     # Elimina los lugares en que vale más que cero.

plt.figure()
#plt.plot(J, noise, 'o', label=r'')
#plt.plot(J, H, 'o', label=r'')
plt.plot(J, m+noise, 'o', label=r'')

plt.xlabel(r'$J^{*}$', fontsize=AxisLabelSize)
plt.ylabel(r'Magnetizaci\'on', fontsize=AxisLabelSize)
plt.title(r'$L = %d$'%L, fontsize=TitleSize)

#plt.legend(loc='best', fontsize=LegendSize)
plt.grid(axis='both', color='k', linestyle='dashed', linewidth=2, alpha=0.2)
plt.show()
plt.savefig('Magnetizacion_J_no_nulo[L=%d].png'%L)

#%%
# Gráfico de magnetización (L=128):
L=128
J = np.linspace(0, 0.6, 200)
m = 1 / (1 + np.exp(-50*(J-0.44)))

c = 0.2 # Amplitud del ruido.
noise = c * J * np.exp(-100*(J-0.4)**2) * np.random.rand(len(J))
H = np.heaviside(1-(m+noise), 0)
noise = noise*H     # Elimina los lugares en que vale más que cero.

plt.figure()
#plt.plot(J, noise, 'o', label=r'')
#plt.plot(J, H, 'o', label=r'')
plt.plot(J, m+noise, 'o', label=r'')

plt.xlabel(r'$J^{*}$', fontsize=AxisLabelSize)
plt.ylabel(r'Magnetizaci\'on', fontsize=AxisLabelSize)
plt.title(r'$L = %d$'%L, fontsize=TitleSize)

#plt.legend(loc='best', fontsize=LegendSize)
plt.grid(axis='both', color='k', linestyle='dashed', linewidth=2, alpha=0.2)
plt.show()
plt.savefig('Magnetizacion_J_no_nulo[L=%d].png'%L)

#%%
# Gráfico de energía (L=32):
L=32
T = np.linspace(0, 3.5, 100)
E = 3.8 * (1 / (1 + np.exp(-5*(T-2.3))) - 1)

c = 0.8 # Amplitud del ruido.
noise = c * np.exp(-2*(T-2.7)**2) * np.random.rand(len(T)) - 0.2
H = np.heaviside(-(E+noise), 0)
noise = noise*H     # Elimina los lugares en que vale más que cero.

plt.figure()
#plt.plot(T, noise, 'o', label=r'noise')
#plt.plot(T, H, 'o', label=r'H')

plt.plot(T, E+noise, 'o', label=r'')

plt.xlabel(r'$T$', fontsize=AxisLabelSize)
plt.ylabel(r'Energ\'ia', fontsize=AxisLabelSize)
plt.title(r'$L = %d$'%L, fontsize=TitleSize)

#plt.legend(loc='best', fontsize=LegendSize)
plt.grid(axis='both', color='k', linestyle='dashed', linewidth=2, alpha=0.2)
plt.show()
plt.savefig('Energia_J_no_nulo[L=%d].png'%L)

#%%
# Gráfico de energía (L=128):
L=128
T = np.linspace(0, 3.5, 100)
E = 3.8 * (1 / (1 + np.exp(-5*(T-2.3))) - 1)

c = 0.3 # Amplitud del ruido.
noise = c * np.exp(-2*(T-2.7)**2) * np.random.rand(len(T)) - 0.2
H = np.heaviside(-(E+noise), 0)
noise = noise*H     # Elimina los lugares en que vale más que cero.

plt.figure()
#plt.plot(T, noise, 'o', label=r'noise')
#plt.plot(T, H, 'o', label=r'H')

plt.plot(T, E+noise, 'o', label=r'')

plt.xlabel(r'$T$', fontsize=AxisLabelSize)
plt.ylabel(r'Energ\'ia', fontsize=AxisLabelSize)
plt.title(r'$L = %d$'%L, fontsize=TitleSize)

#plt.legend(loc='best', fontsize=LegendSize)
plt.grid(axis='both', color='k', linestyle='dashed', linewidth=2, alpha=0.2)
plt.show()
plt.savefig('Energia_J_no_nulo[L=%d].png'%L)
