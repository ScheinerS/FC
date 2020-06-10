import numpy as np
import matplotlib.pyplot as plt

correlacion = np.loadtxt('correlacion(delta=0.1).csv', skiprows=1, delimiter=' ', unpack=True) 

i=correlacion[0] #numero de pasos
L=correlacion[1] #valores de x
M=correlacion[2] #valores de w, 
C=correlacion[3] #valores de correlacion

#%%
#Histograma de la distribucion de pasos para delta=1

plt.hist(L, bins=70)

plt.title('Delta=1.0', fontsize=16)
plt.xlabel('x', fontsize=14)
plt.ylabel('', fontsize=14)

plt.grid()
plt.legend()
plt.show()

#%%
#Histograma de la distribucion de pasos para delta=0.1

plt.hist(L, bins=70)

plt.title('Delta=0.1', fontsize=16)
plt.xlabel('x', fontsize=14)
plt.ylabel('', fontsize=14)

plt.grid()
plt.legend()
plt.show()

#%%
##Debería ser el gráfico para la correlación, pero todavía no lo sé hacer.
plt.plot(i, C, '.r', label='delta=0.1' )

plt.title('', fontsize=16)
plt.xlabel('pasos', fontsize=14)
plt.ylabel('correlación', fontsize=14)

plt.grid()
plt.legend()
plt.show()