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

if os.name == 'posix':   # Linux
    Linux = True

plt.rc('text', usetex=Linux)
plt.rc('font', family='serif')

#%%

x1=[] #Probabilidad dim = 4
y1=[] #Intensidad cluster percolante dim = 4

fit=[]
fit_fn=[]

with open("masa", "r") as f:
    plots = csv.reader(f, delimiter=" ")
    for row in plots:
        if len(row)==0 :
            pass
        else:
            x1.append(float(row[0]))
            y1.append(float(row[1]))
            

fit.append(np.polyfit(np.log(x1), np.log(y1), 1))
fit_fn.append(np.poly1d(fit[0]))
plt.plot(np.log(x1), fit_fn[0](np.log(x1)), '--k')


plt.plot(np.log(x1),np.log(y1),"o")

#plt.legend(loc='best', fontsize=LegendSize)
plt.title(r"Masa de Cluster Percolante vs Dimensi\'on", fontsize=TitleSize)
plt.xlabel(r"Dimensi\'on", fontsize=AxisLabelSize)
plt.ylabel(r"Masa Cluster Percolante", fontsize=AxisLabelSize)
plt.grid(axis='both', color='k', linestyle='dashed', linewidth=2, alpha=0.2)

plt.show()


if Linux:
    plt.savefig(path + '/masa.png')