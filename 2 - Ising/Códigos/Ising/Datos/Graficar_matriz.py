import numpy as np
import matplotlib.pyplot as plt

L=32

red = np.loadtxt("red_L=%d.txt"%L)#, dtype='i', delimiter=' ')

plt.imshow(red,cmap='hot_r') # gist_heat_r, hot_r # poner cualquier cosa para ver lista completa.
    #coolwarm, viridis, plasma, inferno, magma, cividis

plt.savefig("red_L=%d.png"%L)
