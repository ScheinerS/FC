import matplotlib.pyplot as plt
import csv
import numpy as np

xt=[]
yt=[]

name=[]

for i in range(1,51):
    xt.append(i/100)

for i in range(1,15):
    yt.append([])
    name.append("gamma_"+str(i)+"_dim_8")
    with open(name[i-1], "r") as f:
        plots = csv.reader(f, delimiter=" ")
        for row in plots:
            yt[i-1].append(float(row[1]))
            
suma=[]

for i in range(50):
    suma.append(0)

for i in range(0,50):
    for j in range(1,15):
        suma[i]+=yt[j-1][i]*(j**2)
        
        
plt.plot(xt,suma,"o")
plt.show()

xd=xt[37:48]
xi=xt[27:38]

yd=[]
yi=[]

for i in range(len(xd)):
    yd.append(-67569.97036364*xd[i]+53290.60052909)
    yi.append(93881.31872727*xi[i]-8400.49410727)

for i in range(len(yd)):
    if yd == yi:
        print(yd)