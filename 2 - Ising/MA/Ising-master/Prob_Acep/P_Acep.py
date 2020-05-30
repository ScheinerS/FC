import matplotlib.pyplot as plt
import numpy as np
import csv

x=[]
y=[]

with open("Prob_Acep.txt", "r") as file:
    plots = csv.reader(file, delimiter = " ")
    for row in plots:
        x.append(float(row[0]))
        y.append(float(row[1]))
        
#Y=list(set(y))
#Y.sort()
plt.plot(x,y)

print(y)
