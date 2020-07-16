#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Gráfico del potencial de Lennard-Jones para la introducción.
"""

import sys
import os
import matplotlib.pyplot as plt
from matplotlib import rcParams, cycler
#import csv
import numpy as np
#import pandas as pd

path = os.path.dirname(os.path.realpath('__file__'))
sys.path.append(path)

TitleSize = 15
AxisLabelSize = 15
LegendSize = 14
NumberSize = 12

plt.close('all')

if os.name == 'posix':
    Linux = True

plt.rc('text', usetex=Linux)
plt.rc('font', family='serif')

# Para una transición suave de colores entre las curvas:
N_curvas = 5    # cantidad de curvas
cmap = plt.cm.summer #coolwarm, viridis, plasma, inferno, magma, cividis
rcParams['axes.prop_cycle'] = cycler(color=cmap(np.linspace(0, 1, N_curvas)))

e=1
sigma = [1]

r = np.linspace(0.97,2.1,100)

plt.figure()

for s in sigma:
    u = 4*e*((s/r)**12 - (s/r)**6)

    plt.plot(r, u, label=r'$\sigma = %g$'%s)

plt.xlabel(r'$r$', fontsize=AxisLabelSize)
plt.ylabel(r'$u(r)$', fontsize=AxisLabelSize)
plt.title(r'', fontsize=TitleSize)

plt.legend(loc='best', fontsize=LegendSize)
plt.grid(axis='both', color='k', linestyle='dashed', linewidth=2, alpha=0.2)
plt.show()
plt.savefig('Gráficos/Lennard-Jones.png')