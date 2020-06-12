//Función Trial. Nos dice el tamaño de laso que damos, desde x0 hasta x.
#define DELTA 1
double trial(double x0)
{
double p,x;
p = myrand();
x = 2.0*DELTA*(p-0.5)+x0;
return x;
}