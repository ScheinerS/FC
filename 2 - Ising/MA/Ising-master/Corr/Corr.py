import csv
import matplotlib.pyplot as plt

delta=[]
xs=[]
suma=[]
suma2=[]
sumaij0=[]
sumaij1=[]
sumaij2=[]
sumaij3=[]
sumaij4=[]
sumaij5=[]
sumaij6=[]
sumaij7=[]
sumaij8=[]
sumaij9=[]
name=[sumaij0,sumaij1,sumaij2,sumaij3,sumaij4,sumaij5,sumaij6]
paso=[0,2,4,6,8,10,20]
corr=[]

j=0

for i in range(41):
    suma.append(0)
    suma2.append(0)
    sumaij0.append(0)
    sumaij1.append(0)
    sumaij2.append(0)
    sumaij3.append(0)
    sumaij4.append(0)
    sumaij5.append(0)
    sumaij6.append(0)
    xs.append([])
    
for i in range(3):
    corr.append([])

with open("Corr.txt", "r") as file:
    plots = csv.reader(file, delimiter = " ")
    for row in plots:
        if len(row) == 1:
            delta.append(float(row[0]))
            j+=1
        if len(row) == 2:
            xs[j-1].append(float(row[1]))
            
for i in range(len(xs)):
    for j in range(999999):
        suma[i]+=xs[i][j]/(1000000-1)
        suma2[i]+=(xs[i][j]**2)/(1000000-1)
    suma[i]=suma[i]**2

for i in range(41):
    sumaij0[i]=suma2[i]
        
for i in range(41):
    for j in range(999997):
        sumaij1[i]+=xs[i][j+2]*xs[i][j]
    sumaij1[i]=sumaij1[i]/999997
        
for i in range(41):
    for j in range(999995):
        sumaij2[i]+=xs[i][j+4]*xs[i][j]
    sumaij2[i]=sumaij2[i]/999995

for i in range(41):
    for j in range(999993):
        sumaij3[i]+=xs[i][j+6]*xs[i][j]
    sumaij3[i]=sumaij3[i]/999993
    
for i in range(41):
    for j in range(999991):
        sumaij4[i]+=xs[i][j+8]*xs[i][j]
    sumaij4[i]=sumaij4[i]/999991
    
for i in range(41):
    for j in range(999989):
        sumaij5[i]+=xs[i][j+10]*xs[i][j]
    sumaij5[i]=sumaij5[i]/999989
    
for i in range(41):
    for j in range(999979):
        sumaij6[i]+=xs[i][j+20]*xs[i][j]
    sumaij6[i]=sumaij6[i]/999979

for i in range(1,4):
    for j in range(7):
        corr[i-1].append((name[j][i*10]-suma[i*10])/(suma2[i*10]-suma[i*10]))            
            
plt.plot(paso,corr[0],label="Delta=2,7")
plt.plot(paso,corr[1],label="Delta=2,8")
plt.plot(paso,corr[2],label="Delta=2,9")

plt.xlabel("Paso")
plt.ylabel("Correlación")
plt.legend()

plt.savefig("Corr-Paso.png")

plt.show()
            