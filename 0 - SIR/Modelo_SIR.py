# -*- coding: utf-8 -*-
"""
Created on Wed Apr 22 10:54:45 2020

@author: Alumno
"""

import scipy.integrate as spi
import numpy as np
import matplotlib.pyplot as plt

plt.close('all')
plt.rc('text', usetex=True)
plt.rc('font', family='serif')

TitleSize = 20
AxisLabelSize = 16
LegendSize = 14
NumberSize = 10

#%%

'''tamaño poblacional'''
N = 1     # cantidad de individuos de la población
tau = 0.6 # prob de infectar dado el contacto
C = 1/6   # frecuencia de los contactos
d = 30    # duración de la infectividad

beta = tau*C
nu = 1/d
R_0 = beta/nu

'''condiciones iniciales'''
TS=1
ND=365
I0=1e-6
S0=1-I0
INPUT = (S0, I0, 0.0)

'''Ec diferencial'''
def diff_eqs(INP,t):
    Y=np.zeros((3))
    V = INP
    Y[0] = - beta * V[0] * V[1]
    Y[1] = beta * V[0] * V[1] - nu * V[1]
    Y[2] = nu * V[1]
    return Y   # For odeint

t_start = 0.0; t_end = ND; t_inc = TS
t_range = np.arange(t_start, t_end+t_inc, t_inc)
RES = spi.odeint(diff_eqs,INPUT,t_range)
print('R_0: %.2f'%R_0)


#%%

plt.figure()


plt.plot(RES[:,0]*N, color='orange', label='Susceptibles')
plt.plot(RES[:,2]*N, '-k', label='Recuperados')
plt.plot(RES[:,1]*N, '-r', label='Infectados')

plt.legend(loc='best', fontsize=LegendSize)
plt.title(r'$R_{0} = %.2f$'%(R_0), fontsize=TitleSize)

plt.xlabel(r'Tiempo (d\'ias)', fontsize=AxisLabelSize)
plt.ylabel(r'Proporci\'on de la poblaci\'on', fontsize=AxisLabelSize)

plt.grid(axis='both', color='k', linestyle='dashed', linewidth=2, alpha=0.2)
plt.show()

plt.savefig('SIR-R_0=%.2f.png'%(R_0))
