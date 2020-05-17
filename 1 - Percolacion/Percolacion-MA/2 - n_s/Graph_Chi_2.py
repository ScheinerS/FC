import sys
import os
import matplotlib.pyplot as plt
from matplotlib import rcParams, cycler
import csv
import numpy as np
#from scipy.stats import chisquare

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

x1=[]
x2=[]
x3=[]
x4=[]
x5=[]
x6=[]
x7=[]
x8=[]
x9=[]

x1f=[]
x2f=[]
x3f=[]
x4f=[]
x5f=[]
x6f=[]
x7f=[]
x8f=[]
x9f=[]

y1=[]
y2=[]
y3=[]
y4=[]
y5=[]
y6=[]
y7=[]
y8=[]
y9=[]

y1f=[]
y2f=[]
y3f=[]
y4f=[]
y5f=[]
y6f=[]
y7f=[]
y8f=[]
y9f=[]

xs=[x1,x2,x3,x4,x5,x6,x7,x8,x9]
ys=[y1,y2,y3,y4,y5,y6,y7,y8,y9]

xsf=[x1f,x2f,x3f,x4f,x5f,x6f,x7f,x8f,x9f]
ysf=[y1f,y2f,y3f,y4f,y5f,y6f,y7f,y8f,y9f]

fit=[]
fit_fn=[]

ps=[]
style=['co','mo',"ro","go","bo","ko","o","co","mo",'o']

#x1 es s de p1, x2 es s de p2, ...
#y1 es n_s de p1, y2 es s de p2, ...

i=0


with open("n_s128", "r") as f:
    plots = csv.reader(f, delimiter=" ")
    for i in range(0,len(xs)):
        for row in plots:    
            if len(row)==0 :
                i+=1
            elif len(row)==1 :
                ps.append(str(row[0]))
            else:
                xs[i].append(float(row[0]))  #s
                ys[i].append(float(row[1]))  #n_s
        
        
#=============================================================================
for i in range(len(xs)):
    for j in range(len(xs[i])):
        if ys[i][j] >= 1:
            xsf[i].append(xs[i][j])
            ysf[i].append(ys[i][j])
 
#%%
            
# Para una transición suave de colores entre las curvas:
N=8    # porque tenemos 16 curvas
cmap = plt.cm.hot #coolwarm, viridis, plasma, inferno, magma, cividis
rcParams['axes.prop_cycle'] = cycler(color=cmap(np.linspace(0, 1, N)))

for i in range(2,len(xsf)-2):
    #plt.plot(np.log(xsf[i]),np.log(ysf[i]),style[i],label="Prob. "+ps[i+1])
    plt.plot(np.log(xsf[i]),np.log(ysf[i]),'o',label="Prob. "+ps[i+1])          
    fit.append(np.polyfit(np.log(xsf[i]), np.log(ysf[i]), 1))
    fit_fn.append(np.poly1d(fit[i-2]))
    plt.plot(np.log(xsf[i]), fit_fn[i-2](np.log(xsf[i])), '--k')
    print("Probabilidad %s" %(ps[i+1]))
   # print(chisquare(ysf[i],fit_fn[i-2](np.log(xsf[i]))))
    print("Tau = %f" %(fit[i-2][0]))


#plt.figure()
plt.xlabel(r'$\log(s)$', fontsize=AxisLabelSize)
plt.ylabel(r'$\log(n_{s})$', fontsize=AxisLabelSize)

plt.title(r'$L=128$', fontsize=TitleSize)
plt.legend(loc='best', fontsize=LegendSize)
plt.grid(axis='both', color='k', linestyle='dashed', linewidth=2, alpha=0.2)
plt.show()

if Linux:
    plt.savefig("Chi_128.png")


#%%

for i in range(4):
    E=fit_fn[i](np.log(xsf[i]))
    O=ysf[i]
    chi_2 = 0
    
    for j in range(len(E)):
        chi_2 += ((O[j]-E[j])**2)/E[j]
    
    print(len(ysf[i]))
    print(chi_2/len(ysf[i]))
    
#=============================================================================
    
