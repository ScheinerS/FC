import csv
import math as m
import matplotlib.pyplot as plt

x=[]
y=[]

f=0

with open("Calculo_Integral.txt", "r") as file:
    plots = csv.reader(file, delimiter = " ")
    for row in plots:
        x.append(float(row[0]))
        
X=list(set(x))
X.sort()
       
 
for i in range(len(X)):
    y.append(m.exp((-(X[i])**2)/2))

for i in range(len(X)-1):
    f+=((X[i])**2) * (y[i]) * (X[i+1] - X[i])

plt.plot(X,y,"o")

plt.show()

print("El valor de la integral es "+str(f))

def remove_duplicates(a): 
    t=[]
    
    b = set(a)
    
    for t in b:
        t.append(a.remove())
    return t

#print(x)
#print(remove_duplicates(x))