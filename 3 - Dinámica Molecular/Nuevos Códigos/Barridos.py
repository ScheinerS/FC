#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Jul 25 17:23:26 2020

@author: ramiro
"""

import numpy as np
import matplotlib.pyplot as plt

TitleSize = 15
AxisLabelSize = 15
LegendSize = 12


data = np.loadtxt('Barrido(T=0.1-2.5,rho=1).dat', skiprows=1, delimiter=' ', unpack=False)

Ekin    =data[:,0]
Epot    =data[:,1]
Etot    =data[:,2]
Temp    =data[:,3]
Pres    =data[:,4]
a=len(Ekin)
iteracion=np.linspace(1,a,a)

plt.figure()
plt.plot(Temp,Pres)

plt.xlabel(r'Temperatura', fontsize=AxisLabelSize)
plt.ylabel(r'Presión', fontsize=AxisLabelSize)
plt.title(r'', fontsize=TitleSize)

plt.legend(loc='best', fontsize=LegendSize)
plt.grid()
plt.show()