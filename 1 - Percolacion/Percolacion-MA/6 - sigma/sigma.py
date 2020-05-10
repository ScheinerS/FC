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

if os.name == 'posix':
    Linux = True

plt.rc('text', usetex=Linux)
plt.rc('font', family='serif')

#%%
epsilon=[]

for i in range(0,1):
    with open("pmax", "r") as f:
        plots = csv.reader(f, delimiter=" ")
        for row in plots:
            epsilon.append(float(row[0]))

#epsilon.pop(11)
#epsilon.pop(11)


epsilon=np.abs(epsilon)

s=[]

fit=[]
fit_fn=[]

for i in range(2,17):
    s.append(i)

#s.pop(11)
#s.pop(11)

#%%
#plt.figure()
fit.append(np.polyfit(np.log(s), np.log(epsilon), 1))
fit_fn.append(np.poly1d(fit[0]))
plt.plot(np.log(s), fit_fn[0](np.log(s)), '--k')

    
plt.plot(np.log(s),np.log(epsilon),"o")



plt.xlabel(r'log(s)', fontsize=AxisLabelSize)
plt.ylabel(r'$\log(\epsilon)$', fontsize=AxisLabelSize) 
#plt.title(r'Ajuste Exponente Sigma', fontsize=TitleSize)


#plt.legend(loc='best', fontsize=LegendSize)
plt.grid(axis='both', color='k', linestyle='dashed', linewidth=2, alpha=0.2)
plt.show()

if Linux:
    plt.savefig("exponente_sigma_32.png")


print(fit_fn)