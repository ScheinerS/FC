#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
import os
import matplotlib.pyplot as plt
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

#%%
# FALTA AGREGAR CUANDO ESTÉN HECHOS:

# Tamaño de la red:
L=32

# Datos de la simulación:
# magnetizacion = np.loadtxt('   .csv', skiprows=1, delimiter=' ', unpack=True)
# energia = np.loadtxt('   .csv', skiprows=1, delimiter=' ', unpack=True)

# Valores esperados:
B = np.linspace(0, 5, 200)
magnetizacion = np.tanh(B)
energia = -B*np.tanh(B)*L*L
#susceptibilidad = -B*np.tanh(B)*L*L
#%%
# Gráfico de magnetización:

plt.figure()
plt.plot(B, magnetizacion, 'ok', label=r'Simulado')
plt.plot(B, magnetizacion, '-r', label=r'Esperado')

plt.xlabel(r'$B^{*}$', fontsize=AxisLabelSize)
plt.ylabel(r'Magnetizaci\'on por sitio', fontsize=AxisLabelSize)
plt.title(r'', fontsize=TitleSize)

plt.legend(loc='best', fontsize=LegendSize)
plt.grid(axis='both', color='k', linestyle='dashed', linewidth=2, alpha=0.2)
plt.show()
plt.savefig('Magnetizacion_por_sitio.png')


#%%
# Gráfico de energía:

plt.figure()
plt.plot(B, energia, 'ok', label=r'Simulado')
plt.plot(B, energia, '-r', label=r'Esperado')

plt.xlabel(r'$B^{*}$', fontsize=AxisLabelSize)
plt.ylabel(r'Energ\'ia', fontsize=AxisLabelSize)
plt.title(r'', fontsize=TitleSize)

plt.legend(loc='best', fontsize=LegendSize)
plt.grid(axis='both', color='k', linestyle='dashed', linewidth=2, alpha=0.2)
plt.show()
plt.savefig('Energia.png')

#%%
# Gráfico de susceptibilidad:

plt.figure()
#plt.plot(, , 'ok', label=r'Simulado')
#plt.plot(B, susceptibilidad, '-r', label=r'Esperado')

plt.xlabel(r'$B^{*}$', fontsize=AxisLabelSize)
plt.ylabel(r'Susceptibilidad', fontsize=AxisLabelSize)
plt.title(r'', fontsize=TitleSize)

plt.legend(loc='best', fontsize=LegendSize)
plt.grid(axis='both', color='k', linestyle='dashed', linewidth=2, alpha=0.2)
plt.show()
#plt.savefig('Susceptibilidad.png')