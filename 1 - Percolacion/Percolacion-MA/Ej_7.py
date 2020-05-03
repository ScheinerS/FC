from scipy.optimize import brentq
import numpy as np

def cero_p_perv(x):
    return 2*x**2-x**4-x

def p_perv_der(x):
    return 4*x-4*x**3

def cero_p_Msimple(x):
    return 4*x**3-3*x**4-x

def p_Msimple_der(x):
    return 12*x**2-12*x**3

p_c_perv = brentq(cero_p_perv,0.2,0.9)
p_c_Msimple = brentq(cero_p_Msimple, 0.2, 0.9)

nu_perv = np.log(2)/np.log(p_perv_der(p_c_perv))
nu_Msimple = np.log(2)/np.log(p_Msimple_der(p_c_Msimple))

print("p_c_perv = "+str(p_c_perv)+" y gamma_perv = "+str(nu_perv))
print("p_c_Msimple = "+str(p_c_Msimple)+" y gamma_Msimple = "+str(nu_Msimple))