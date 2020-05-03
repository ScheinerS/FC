import matplotlib.pyplot as plt
import csv


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

name=["Dim. 4","Dim. 8","Dim. 16","Dim. 32","Dim. 64","Dim. 128"]

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
            

for i in range(6):
    plt.plot(xs[i],ys[i],label=name[i])

    
plt.xlabel("Probabilidad")
plt.ylabel("Intensidad Cluster Percolante")

plt.title("Intensidad de Cluster Percolante vs Probabilidad")
plt.legend()
plt.show()
        