import matplotlib.pyplot as plt
import csv
import numpy as np

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

fit.append(np.polyfit(np.log(s), np.log(epsilon), 1))
fit_fn.append(np.poly1d(fit[0]))
plt.plot(np.log(s), fit_fn[0](np.log(s)), '--k')

    
plt.plot(np.log(s),np.log(epsilon),"o")

    
plt.xlabel("log(s)")
plt.ylabel("log(ε)")
plt.title("Ajuste Exponente Sigma")

#plt.axis([0.1,0.7,0,100])
plt.legend()

plt.savefig("Ajuste Sigma_32.png")
plt.show()
        
print(fit_fn)
