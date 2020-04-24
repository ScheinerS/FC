# -*- coding: utf-8 -*-
"""
Created on Wed Apr 22 10:54:45 2020

@author: Alumno
"""

import scipy.integrate as spi
import numpy as np
import matplotlib.pyplot as plt
'''tamaño poblacional'''
N=1#número de la población
tau=0.6#prob de infectar dado el contacto
C=1/5#frecuencia de los contactos
d=30#duración de la infectividad

beta=tau*C
nu=1/d
R_0=beta/nu

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
print('R_0:')
print(beta/nu)
#Gráfica
plt.plot(RES[:,0]*N, '-g', label='Susceptibles')
plt.plot(RES[:,2]*N, '-k', label='Recuperados')
plt.plot(RES[:,1]*N, '-r', label='Infectados')
plt.legend(loc=0)
plt.title('Modelo SIR')
plt.xlabel('Tiempo')
plt.grid()
'''guardamos la imagen'''
#plt.savefig('sirpy')
