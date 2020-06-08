#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define L        8
#define SEMILLA  283048
#define ITER     2000
#define SMIN     1          // cluster minimo a analizar
#define SMAX     16         // cluster maximo a analizar

int poblar (int *red, double p, int dim);
int etiqueta_verdadera(int *historial, int s);
int etiqueta_falsa(int *red,int *historial, int S1, int S2, int i, int j, int dim);
int clasificar(int *red,int dim);
int percola(int *red,int *percolantes,int n);
int inicializar_ns(double *ns,int dim);
int inicializar_percolantes(int *percolantes,int dim);
double histograma(int *red,int *percolantes,double *ns,int dim);
double momento2(double *ns,double suma,int dim);

//Función principal:

int main()
{ 
  int    i,dim,*red,*percolantes;
  double p,suma,m2,*ns,Porcentaje;
  FILE   *fp;

  dim = L;

  srand(SEMILLA);

  red = malloc(dim*dim*sizeof(int));                  //Reserva el espacio necesario para la red.
  ns  = malloc(dim*dim*sizeof(double));               //Reserva el espacio necesario para el histograma.
  percolantes = (int*) malloc(dim*dim*sizeof(int));   //Reserva el espacio necesario para losclusters percolantes.

  
  fp = fopen("gamma8_ramiro_santiago_m2(4-16).csv","w");


  for(p=0.4;p<0.8;p=p+0.0005)
  { 
    suma = 0.0;
    inicializar_ns(ns,dim);

    for (i=0;i<ITER;i++)
      {
        inicializar_percolantes(percolantes,dim);

        poblar(red,p,dim);
        clasificar(red,dim);
        percola(red,percolantes,dim);                 // hallaas los clusters percolantes (para luego eliminarlos)
    
        suma += histograma(red,percolantes,ns,dim);   // calculas la distribucion de fragmentos ns

      }

    Porcentaje=(p-0.4)/0.4;

    printf("Total:\t%f / %i\r", Porcentaje, 1);
	fflush(stdout);

    m2 = momento2(ns,suma,dim);                       // calculas el momento de orden 2 para ns(p)

    fprintf(fp,"%lf %lf\n",p,m2);
	

    
	//printf("%lf %lf\n",p,m2);
  }


  fclose(fp);

  free(ns);
  free(red);
  free(percolantes);

  return 0;
}



//Funciones secundarias:

int poblar(int *red, double p, int dim)
{ double random;
  int i;

  for (i=0;i<dim*dim;i++)                           //Toma como rango máximo la cantidad de celdas totales.
    { *(red+i)=0;                                   //Asigna por defecto el valor <vacio>
      random=((double)rand())/((double) RAND_MAX);  //Valor aleatorio entre 0 y 1.
      if (random<p)
      {*(red+i)=1;
      }                                             //Asigna como <lleno> si el valor aleatorio es menor.
    }

  return 0;
}


int clasificar(int *red,int dim)
{ int S1,S2,i,j,frag;
  int *historial;

  //Creo la tira historial:
  historial = malloc((dim*dim)/2*sizeof(int));
  for(i=0;i<=(dim*dim)/2;i++)
  { *(historial+i) = i;
  }

  frag = 2;

  if(*(red)) //Primer lugar.
  { *(red) =frag;
    frag++;
  }

  for(i=1;i<dim;i++) //Primera fila sin primer lugar.
  { S1= *(red+i-1);
    if(*(red+i) && S1)  //S1 es 1.
    { *(red+i) = etiqueta_verdadera(historial, S1);
    }
    if(*(red+i) && !S1)  //S1 es 0.
    { *(red+i)=frag;
      frag++;
    }
  }

  for(i=1;i<dim;i++)  //Primera columna sin primer lugar.
  { S2 = *(red+(i*dim-dim));
    if(*(red+(i*dim)) && S2)  //S2 es 1.
    { *(red+(i*dim)) = etiqueta_verdadera(historial, S2);
    }
    if(*(red+(i*dim)) && !S2)  //S2 es 0.
    { *(red+(i*dim))=frag;
      frag++;
    }
  }

  for(i=1;i<dim;i++) //Todo el resto.
  { for(j=1;j<dim;j++)
    { S1 = *(red+(i*dim+j-1)); //El casillero de la izquierda.
      S2 = *(red+(i*dim+j-dim)); //El casillero de arriba.

      if( *(red+(i*dim+j)) && (S1 || S2)) // Acá entran cuando los dos o uno de ellos son 1.
      { if (S1 && S2 && (etiqueta_verdadera(historial, S2)<etiqueta_verdadera(historial, S1))) //Los dos son 1 y S1 más grande.
        { *(red+(i*dim+j)) = etiqueta_verdadera(historial, S2);
          *(historial+S1) = -abs(*(historial+S2));
        }
        if (S1 && S2 && (etiqueta_verdadera(historial, S1)<etiqueta_verdadera(historial, S2))) //Los dos son 1 y S2 más grande.
        { *(red+(i*dim+j)) = etiqueta_verdadera(historial, S1);
          *(historial+S2) = -abs(*(historial+S1));
        }
        if (S1 && S2 && (etiqueta_verdadera(historial, S2)==etiqueta_verdadera(historial, S1))) //Los dos son 1 y son iguales, elijo arbitrariamente S2.
        { *(red+(i*dim+j))=etiqueta_verdadera(historial, S2);
        }
        if ((!S1) && S2) //S1 es cero y S2 es 1.
        { *(red+(i*dim+j))=etiqueta_verdadera(historial, S2);
        }
        if (S1 && (!S2)) //S1 es 1 y S2 es cero.
        { *(red+(i*dim+j))=etiqueta_verdadera(historial, S1);
        }
       }

      if ( *(red+(i*dim+j)) && ((!S1) && (!S2))) //los dos son cero.
      { *(red+(i*dim+j))=frag;
        frag++;
      }
    }
  }

  for(i=0; i<dim*dim/2; i++)
  { *(historial+i)=etiqueta_verdadera(historial, i);
  }


  for(i=0;i<dim*dim;i++)
  { *(red+i) = *(historial+*(red+i));
  }

  free(historial);

  return 0;

  }

int etiqueta_verdadera(int *historial, int s)
{ while(*(historial+s)<0)
  { s = - *(historial+s);
  }
  return *(historial+s);
}

int inicializar_ns(double *ns,int dim)
{
  int i;

  for(i=0; i<dim*dim; i++)  *(ns + i) = 0.0;

  return 1;
}


int inicializar_percolantes(int *percolantes,int dim)
{
  int i;

  for(i=0; i<dim*dim; i++)  *(percolantes + i) = 0;

  return 1;
}

int percola(int *red,int *percolantes,int n)
{
  // esta funcion devuelve los fragmentos percolantes 
  // en el puntero *percolantes

  int i,j,k,*renglon1,*renglon2;

  renglon1 = (int*) malloc(n*n*sizeof(int));
  renglon2 = (int*) malloc(n*n*sizeof(int));

  for (i=0;i<n*n;i++)
    {
      *(renglon1+i) = 0;
      *(renglon2+i) = 0;
    }

  for (i=0;i<n;i++)
    {
      j = *(red+i);
      *(renglon1+j) = 1;

      j = *(red+n*(n-1)+i);
      *(renglon2+j) = 1;
    }  

  for (i=1;i<n*n;i++)
    {
      j = *(renglon1+i);
      k = *(renglon2+i);

      if (j && k) *(percolantes+i) = 1;
    }

  free(renglon1);
  free(renglon2);

  return 1;
}

double histograma(int *red,int *percolantes,double *histo,int n)
{
  // *red es la red ya clasificada
  // *percolantes contiene "1" si esa posicion corresponde a una
  // etiqueta percolante.
  // *histo es la distribucion de fragmantos sin normalizar 
  // n es el lado de la red

  int    i,j,*masas;
  double s;

  s = 0.0;

  masas = (int*) malloc(n*n*sizeof(int));

  for(i=0;i<n*n;i++) *(masas+i) = 0;

  for(i=0;i<n*n;i++)
    {
      j = *(red+i);
      if ((*(percolantes+j))==0) (*(masas+j))++;
    }

  for(i=1;i<n*n;i++)
    {
      j = *(masas+i);
      *(histo+j) = (*(histo+j))+1.0;
      if (j) s = s + 1.0;
    }

  *histo = 0;

  free(masas);

  return s;
}

double momento2(double *histo,double suma,int n)
{
  int    i;
  double s2,m2;

  m2 = 0.0;

  for(i=1;i<n*n;i++) 
    {
      s2 = (double)(i*i);
      m2 += s2*((*(histo+i))/suma);
    }      
  
  return m2;
}


int regresion(double *tr,double *histo,double suma,int n)
{
 // *tr es un puntero de dos valores [R^2, q0 , tau]
 // *histo es la distribución de fragmentos sin normalizar
 // suma es la suma total de los valores de *histo
 // n es el lado de la red

 int    i,m;
 double r,r2,sumX=0,sumX2=0,sumY=0,sumY2=0,sumXY=0,a,b,*x,*y;

 x = (double*) malloc(n*n*sizeof(double));
 y = (double*) malloc(n*n*sizeof(double));

 m = 0;

 sumX = 0.0;
 sumX2= 0.0;
 sumY = 0.0;
 sumY2= 0.0;
 sumXY= 0.0;

 for (i=SMIN;i<SMAX;i++)
   {
     r = (*(histo+i))/suma;

     if (r!=0.0) 
       {
         *(x+m) = log(i);
         *(y+m) = log(r);

         sumX  = sumX + *(x+m);
         sumX2 = sumX2 + (*(x+m))*(*(x+m));
         sumY  = sumY + (*(y+m));
         sumY2 = sumY2 + (*(y+m))*(*(y+m));
         sumXY = sumXY + (*(x+m))*(*(y+m));

         m++;
       }
   }

 // y = a.x+b

 b = (m*sumXY-sumX*sumY)/(m*sumX2-sumX*sumX); // pendiente
 a = (sumY - b*sumX)/m;                       // ordenada al origen

 r2 = (m*sumXY-sumX*sumY)*(m*sumXY-sumX*sumY);
 r2 = r2/((m*sumX2-sumX*sumX)*(m*sumY2-sumY*sumY));

 *(tr+0) = r2;
 *(tr+1) =  a;
 *(tr+2) = -b;

 free(x);
 free(y);

 return 1;
}

