#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int poblar (int *red, float p, int dim);
int contornos(int *red, int dim);
int conteo(int *red, int dim);
int flipeo(int *red, int dim, float Be);
int imprimir(int *red,int dim);


//Función principal:
int main(int argc,char*argv[])
{ float p=0.5, Be=0.01;
  int dim, i, it=100000000, mag=0;
  int *red;
  FILE *magne;

  sscanf(argv[1],"%d",& dim);           //Busca el primero de los argumentos y lo usa como dim.

  dim = dim + 2;

  red = malloc(dim*dim*sizeof(int));    //Reserva el espacio necesario para la red.
  magne = fopen("./Magnetizacion/Magne.txt", "a");
  poblar(red, p, dim);
  contornos(red,dim);
  mag = conteo(red, dim);
  for (i=0; i<it;i++)
    { mag+=flipeo(red, dim, Be);
      contornos(red,dim);
      if(i%10==0)
        {
          fprintf(magne, "%i %i\n", i, mag);
        }
    }

  //printf("%i\n", mag);

  free(red);

  return 0;
}

//Funciones secundarias:
int poblar(int *red, float p, int dim)
{ float random;
  int i, j;

  srand(1);

  for (i=1;i<dim-1;i++)
    { for (j=1;j<dim-1;j++)
      { *(red+i*dim+j)=0;                           //Asigna por defecto el valor <vacio>.
      random=((float)rand())/((float) RAND_MAX);    //Valor aleatorio entre 0 y 1.
      if (random<p)
        {*(red+i*dim+j)=1;                          //Asigna spin pos. si el valor aleatorio es menor.
        }
      else
        {*(red+i*dim+j)=-1;                         //Asigna spin neg. si el valor aleatorio es mayor.
        }
      }
    }

  return 0;
}

int contornos(int *red, int dim)
  { int i;

    for (i=1;i<dim-1;i++)
      { *(red+i) = *(red+(dim-2)*dim+i);        //Contorno Sup.
        *(red+(dim-1)*dim+i) = *(red+dim+i);    //Contorno Inf.
        *(red+i*dim) = *(red+(i+1)*dim-2);      //Contorno Izq.
        *(red+(i+1)*dim-1) = *(red+i*dim+1);    //Contorno Der.
      }

    return 0;
  }

int flipeo(int *red, int dim, float Be)
  { float r;
    float *P_ind;
    int i, j, c=0;

    srand(time(NULL));

    P_ind = malloc(2*sizeof(float));

    *(P_ind) = 1.0/exp(2.0*Be);
    *(P_ind+1) = exp(2.0*Be);

    for (i=1;i<dim-1;i++)
      { for (j=1;j<dim-1;j++)
        { r = ((float)rand())/((float)RAND_MAX);

          if(*(P_ind+((*(red+i*dim+j) + 1)/2))>r)
            { *(red+i*dim+j) = - *(red+i*dim+j);
              if(*(red+i*dim+j)<0)
                {
                  c += -2;
                }
              else
                { c += 2;
                }
            }
          }
        }

    free(P_ind);

    return c;
  }

int conteo(int *red, int dim)
{ int i, j, c=0;

  for (i=1;i<dim-1;i++)
    { for (j=1;j<dim-1;j++)
        {
          c+=*(red+i*dim+j);
        }
    }
    return c;
}

int imprimir(int *red, int dim)         //Imprime una fila debajo de la otra.
{ int i,j;

  for (i=0;i<dim;i++)
    {for (j=0;j<dim;j++)
      {
      printf("%02d ", *(red+dim*i+j));
      }
    printf("\n");
    }

  return 0;
}
