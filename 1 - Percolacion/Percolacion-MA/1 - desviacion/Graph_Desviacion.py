import sys
import os
import matplotlib.pyplot as plt
import csv
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

x1=[]
y1=[]
x2=[]
y2=[]

with open('desviacion.txt','r') as csvfile:
    plots = csv.reader(csvfile, delimiter=" ")
    for row in plots:
        x1.append(float(row[1])) #desviacion
        y1.append(float(row[2])) #probabilidad critica
        x2.append(int(row[0])) #dimension de la red
        
plt.figure()
plt.plot(x1,y1,'o')
plt.xlabel(r'Desviaci\'on', fontsize=AxisLabelSize)
plt.ylabel(r'Probabilidad cr\'itica', fontsize=AxisLabelSize)
plt.title(r'Probabilidad cr\'itica en funci\'on de la dispersi\'on por dimensi\'on', fontsize=TitleSize)
#plt.legend(loc='best', fontsize=LegendSize)
plt.grid(axis='both', color='k', linestyle='dashed', linewidth=2, alpha=0.2)
plt.savefig('sigma_vs_pc.png')
plt.show()


plt.figure()
plt.axhline(y=0.592, linestyle='--', color = 'black', label='0.592')
plt.plot(x2,y1,'ro', label='Simulaciones')
plt.xlabel(r'Dimensi\'on de la red', fontsize=AxisLabelSize)
plt.ylabel(r'Probabilidad cr\'itica', fontsize=AxisLabelSize)
plt.title(r'Probabilidad cr\'itica en funci\'on de la dimensi\'on de la red', fontsize=TitleSize)
plt.legend(loc='best', fontsize=LegendSize)
plt.grid(axis='both', color='k', linestyle='dashed', linewidth=2, alpha=0.2)
plt.savefig('L_vs_pc.png')
plt.show()


plt.figure()
plt.plot(x2,x1,'go')
plt.xlabel(r'Dimensi\'on de la red', fontsize=AxisLabelSize)
plt.ylabel(r'Desviaci\'on', fontsize=AxisLabelSize)
plt.title(r'Desviaci\'on en funci\'on de la dimensi\'on de la red', fontsize=TitleSize)
#plt.legend(loc='best', fontsize=LegendSize)
plt.grid(axis='both', color='k', linestyle='dashed', linewidth=2, alpha=0.2)
plt.savefig('L_vs_sigma.png')
plt.show()
