#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Para hacer los histogramas de percolación.
"""


import sys
import os
import numpy as np
import matplotlib.pyplot as plt

path = os.path.dirname(os.path.realpath('__file__'))
sys.path.append(path)

TitleSize = 20
AxisLabelSize = 15
LegendSize = 12
NumberSize = 12

plt.close('all')

plt.rc('text', usetex=True)
plt.rc('font', family='serif')

#%%

prob = [0.55, 0.59, 0.61]
L = 4
M = 27000 # Automatizar esto.

plt.figure()

for p in prob:
    Y = np.loadtxt(path + "/Datos/histograma_L=%d_M=%d_prob=%.2f.txt"%(L,M,p))
    # Normalizamos el histograma:
    #Y = Y/max(Y)

    X = range(len(Y))


    plt.loglog(X,Y,'.',label='prob = %.2f'%p)

plt.legend(loc='best', fontsize=LegendSize)
plt.title(r'L=%d, %d muestras'%(L,M), fontsize=TitleSize)
plt.xlabel(r'$Tama\tilde{n}o$', fontsize=AxisLabelSize)
plt.ylabel(r'Probabilidad de formaci\'on', fontsize=AxisLabelSize)

# Anotaciones en el gráfico:
#plt.arrow(20, 0, 10, 10)
#plt.annotate(s, (x,y))     # s: anotación, (x,y): coordenadas

plt.grid(axis='both', color='k', linestyle='dashed', linewidth=2, alpha=0.2)
plt.show()

plt.savefig(path + '/Histogramas/Histograma(L=%d,M=%d).png'%(L,M))
