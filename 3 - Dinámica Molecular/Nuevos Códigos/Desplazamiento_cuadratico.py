#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Jul 23 10:08:52 2020

@author: ramiro
"""

import numpy as np
import matplotlib.pyplot as plt

TitleSize = 15
AxisLabelSize = 15
LegendSize = 12


data = np.loadtxt('DCM(T=0.8,rho=0.9).dat', skiprows=1, delimiter=' ', unpack=False)

iteracion=data[:,0]
DCM      =data[:,1]

plt.figure()
plt.plot(iteracion,DCM)

plt.xlabel(r'Iteración', fontsize=AxisLabelSize)
plt.ylabel(r'Desplazamiento Cuadrático', fontsize=AxisLabelSize)
plt.title(r'', fontsize=TitleSize)

plt.legend(loc='best', fontsize=LegendSize)
plt.grid()
plt.show()