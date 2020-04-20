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

TitleSize = 15
AxisLabelSize = 12
LegendSize = 12
NumberSize = 12

plt.close('all')

plt.rc('text', usetex=True)
plt.rc('font', family='serif')

#%%

L=32
M=50000

data = np.loadtxt("Tamaños_L=%d.txt"%(L))
X = data[:,0]
Y = data[:,1]

y_1000 = Y[0:1000]

plt.figure()
#plt.scatter(X,Y)
plt.hist(y_1000,bins=int(np.sqrt(len(y_1000))))

#plt.legend(loc='best', fontsize=LegendSize)
plt.title(r'Tama$\tilde{n}$os de los clusters [L=32, 50000 muestras]', fontsize=TitleSize)
plt.xlabel(r'', fontsize=AxisLabelSize)
plt.ylabel(r'', fontsize=AxisLabelSize)

# Anotaciones en el gráfico:
#plt.arrow(20, 0, 10, 10)
#plt.annotate(s, (x,y))     # s: anotación, (x,y): coordenadas

plt.grid(axis='both', color='k', linestyle='dashed', linewidth=2, alpha=0.2)
plt.show()

plt.savefig(path + '/Histograma(L=%d,M=%d).png'%(L,M))
