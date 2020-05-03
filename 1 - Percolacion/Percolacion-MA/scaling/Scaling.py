import matplotlib.pyplot as plt
import csv
import numpy as np

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


    plt.plot(x_t,y_t,"o",label=name[i-10])

    
plt.xlabel("Probabilidad")
plt.ylabel("n_s/n_s(p_c)")
plt.title("Función f(x)")

#plt.axis([0.1,0.7,0,100])
plt.legend()
plt.show()
        
algo=[]

for i in range(10,36):
    algo.append((i**0.39)*epsilon[i-10])
    
print(len(algo))
print(algo)

