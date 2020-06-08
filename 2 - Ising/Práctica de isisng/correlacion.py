import numpy as np
import matplotlib.pyplot as plt

correlacion = np.loadtxt('correlacion.csv', skiprows=0, delimiter=' ', unpack=True) 

i=correlacion[0]
L=correlacion[1]
M=correlacion[2]
C=correlacion[3]

plt.plot(i, M, '-r', label='y=0.63x' )

plt.title('', fontsize=16)
plt.xlabel('x', fontsize=14)
plt.ylabel('correlación', fontsize=14)

plt.grid()
plt.legend()
plt.show()