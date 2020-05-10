import sys
import os
import matplotlib.pyplot as plt
from matplotlib import rcParams, cycler
import csv
import numpy as np


path = os.path.dirname(os.path.realpath('__file__'))
sys.path.append(path)

TitleSize = 15
AxisLabelSize = 15
LegendSize = 12
NumberSize = 12

plt.close('all')

if os.name == 'posix':   # Linux
    Linux = True

plt.rc('text', usetex=Linux)
plt.rc('font', family='serif')

#%%

name = []

epsilon=[]

for i in range(10,36):
    name.append("scaling_"+str(i))
    with open(name[i-10], "r") as f:
        plots = csv.reader(f, delimiter=" ")
        for row in plots:
            if len(row) == 1:
                epsilon.append(float(row[0]))

epsilon=np.abs(epsilon)

# Para una transición suave de colores entre las curvas:
N=16    # porque tenemos 16 curvas
cmap = plt.cm.viridis #coolwarm, viridis, plasma, inferno, magma, cividis
rcParams['axes.prop_cycle'] = cycler(color=cmap(np.linspace(0, 1, N)))

for i in range(20,36):
    x1=[] #Probabilidad dim = 4
    y1=[] #Intensidad cluster percolante dim = 4

    #fit=[]
    #fit_fn=[]


    with open(name[i-20], "r") as f:
        plots = csv.reader(f, delimiter=" ")
        for row in plots:
            if len(row) == 2:
                x1.append(float(row[0]))
                y1.append(float(row[1]))
            

#fit.append(np.polyfit(np.log(x1), np.log(y1), 1))
#fit_fn.append(np.poly1d(fit[0]))
#plt.plot(np.log(x1), fit_fn[0](np.log(x1)), '--k')

    x_t=[]
    y_t=[]

    for j in range(len(x1)):
        if y1[j] != 0:
            x_t.append(x1[j])
            y_t.append(y1[j])
    plt.semilogy(x_t,y_t,".",label='s='+name[i-10].split('_')[1])
    #plt.plot(x_t,y_t,"o",label=name[i-10])



#plt.legend(loc='best', fontsize=LegendSize)
#plt.title(r"Función f(x)", fontsize=TitleSize)
plt.xlabel(r"Probabilidad", fontsize=AxisLabelSize)
plt.ylabel(r"{n_{s}}/{n_{s}(p_{c})}", fontsize=AxisLabelSize)
plt.grid(axis='both', color='k', linestyle='dashed', linewidth=2, alpha=0.2)
plt.show()
        
algo=[]

for i in range(10,36):
    algo.append((i**0.39)*epsilon[i-10])
    
print(len(algo))
print(algo)

if Linux:
    plt.savefig(path + '/scaling.png')