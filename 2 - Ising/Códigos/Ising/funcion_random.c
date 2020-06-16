//Función de números aleatorios entre cero y uno.

double myrand()
{
double p;
p = (double)rand()/(double)RAND_MAX;
return p;
}