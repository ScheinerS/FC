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

#correlacion = np.loadtxt('correlacion(delta=1).csv', skiprows=1, delimiter=' ', unpack=True) 
#correlacion_01 = np.loadtxt('correlacion(delta=0.1).csv', skiprows=1, delimiter=' ', unpack=True) 

for delta in [0.1, 1]:
    print('%g'%delta)
    correlacion = np.loadtxt('correlacion(delta=%g).csv'%delta, skiprows=1, delimiter=' ', unpack=True) 

    i=correlacion[0] #numero de pasos
    L=correlacion[1] #valores de x
    M=correlacion[2] #valores de w, 
    k=np.linspace(0,499,500)
    C=correlacion[3][0:len(k)] #valores de correlacion


    #Histograma de la distribucion de pasos para delta=1
    plt.figure()
    

    plt.hist(L, bins=70)
    
    plt.xlabel(r'$x$', fontsize=AxisLabelSize)
    plt.ylabel(r'Cantidad de veces', fontsize=AxisLabelSize)
    plt.title(r'$\delta = %g$'%delta, fontsize=TitleSize)
    #plt.legend(loc='best', fontsize=LegendSize)
    plt.grid(axis='both', color='k', linestyle='dashed', linewidth=2, alpha=0.2)
    plt.show()
    plt.savefig('Histograma_delta=%g.png'%delta)


    ## Gráfico de la función de correlación:
    plt.figure()
    plt.plot(k, C, '-r', label='delta=0.1' )

    plt.xlabel(r'Pasos', fontsize=AxisLabelSize)
    plt.ylabel(r'Correlaci\'on', fontsize=AxisLabelSize)
    plt.title(r'$\delta = %g$'%delta, fontsize=TitleSize)
    plt.grid(axis='both', color='k', linestyle='dashed', linewidth=2, alpha=0.2)
    plt.show()
    plt.savefig('Correlacion_delta=%g.png'%delta)