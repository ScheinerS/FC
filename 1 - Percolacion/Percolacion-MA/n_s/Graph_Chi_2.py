from scipy.stats import chisquare
import matplotlib.pyplot as plt
import csv
import numpy as np

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
style=["ro","go","o","bo","ko","yo","go","co","mo"]

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
 
#=============================================================================

for i in range(2,len(xsf)-2):
    plt.plot(np.log(xsf[i]),np.log(ysf[i]),style[i],label="Prob. "+ps[i+1])
    fit.append(np.polyfit(np.log(xsf[i]), np.log(ysf[i]), 1))
    fit_fn.append(np.poly1d(fit[i-2]))
    plt.plot(np.log(xsf[i]), fit_fn[i-2](np.log(xsf[i])), '--k')
    print("Probabilidad %s" %(ps[i+1]))
    print(chisquare(ysf[i],fit_fn[i-2](np.log(xsf[i]))))
    print("Tao = %f" %(fit[i-2][0]))

plt.xlabel("s")
plt.ylabel("n_s")

plt.title("Distribución de Fragmentos en Función del Tamaño.")
plt.legend()
plt.savefig("Chi_128.png")
plt.show()

#=============================================================================
for i in range(4):
    E=fit_fn[i](np.log(xsf[i]))
    O=ysf[i]
    chi_2 = 0
    
    for j in range(len(E)):
        chi_2 += ((O[j]-E[j])**2)/E[j]
    
    print(len(ysf[i]))
    print(chi_2/len(ysf[i]))
    
#=============================================================================
    

    
