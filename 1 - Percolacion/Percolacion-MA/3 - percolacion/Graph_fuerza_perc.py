import sys
import os
import matplotlib.pyplot as plt
from matplotlib import rcParams, cycler
import csv
import numpy as np
from scipy.stats import chisquare

path = os.path.dirname(os.path.realpath('__file__'))
sys.path.append(path)

TitleSize = 20
AxisLabelSize = 20
LegendSize = 12
NumberSize = 12

plt.close('all')

if os.name == 'posix':
    Linux = True

plt.rc('text', usetex=Linux)
plt.rc('font', family='serif')

#%%

x1=[] #Probabilidad dim = 4
y1=[] #Intensidad cluster percolante dim = 4

x2=[] #Probabilidad dim = 8
y2=[] #Intensidad cluster percolante dim = 8

x3=[] #Probabilidad dim = 16
y3=[] #Intensidad cluster percolante dim = 16

x4=[] #Probabilidad dim = 32
y4=[] #Intensidad cluster percolante dim = 32

x5=[] #Probabilidad dim = 64
y5=[] #Intensidad cluster percolante dim = 64

x6=[] #Probabilidad dim = 128
y6=[] #Intensidad cluster percolante dim = 128

xs=[x1,x2,x3,x4,x5,x6]
ys=[y1,y2,y3,y4,y5,y6]

name=["L = 4","L = 8","L = 16","L = 32","L = 64","L = 128"]

with open("perc_4", "r") as f:
    plots = csv.reader(f, delimiter=" ")
    for row in plots:
        if len(row)==0 :
            pass
        else:
            x1.append(float(row[0]))
            y1.append(float(row[1]))
        
with open("perc_8", "r") as f:
    plots = csv.reader(f, delimiter=" ")
    for row in plots:
        if len(row)==0 :
            pass
        else:
            x2.append(float(row[0]))
            y2.append(float(row[1]))
            
with open("perc_16", "r") as f:
    plots = csv.reader(f, delimiter=" ")
    for row in plots:
        if len(row)==0 :
            pass
        else:
            x3.append(float(row[0]))
            y3.append(float(row[1]))
            
with open("perc_32", "r") as f:
    plots = csv.reader(f, delimiter=" ")
    for row in plots:
        if len(row)==0 :
            pass
        else:
            x4.append(float(row[0]))
            y4.append(float(row[1]))

with open("perc_64", "r") as f:
    plots = csv.reader(f, delimiter=" ")
    for row in plots:
        if len(row)==0 :
            pass
        else:
            x5.append(float(row[0]))
            y5.append(float(row[1]))

with open("perc_128", "r") as f:
    plots = csv.reader(f, delimiter=" ")
    for row in plots:
        if len(row)==0 :
            pass
        else:
            x6.append(float(row[0]))
            y6.append(float(row[1]))
            
# Para una transición suave de colores entre las curvas:
N=5    # cantidad de curvas
cmap = plt.cm.inferno #coolwarm, viridis, plasma, inferno, magma, cividis
rcParams['axes.prop_cycle'] = cycler(color=cmap(np.linspace(0, 1, N)))

for i in range(N):
    plt.plot(xs[i],ys[i],label=name[i],zorder=i)

#plt.figure()
plt.xlabel(r'Probabilidad', fontsize=AxisLabelSize)
plt.ylabel(r'Intensidad Cluster Percolante', fontsize=AxisLabelSize)

#plt.title(r'', fontsize=TitleSize)
plt.legend(loc='best', fontsize=LegendSize)
plt.grid(axis='both', color='k', linestyle='dashed', linewidth=2, alpha=0.2)
plt.show()

if Linux:
    plt.savefig("Intensidad_cluster_percolante.png")