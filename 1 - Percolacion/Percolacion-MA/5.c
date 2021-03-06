#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

int poblar (int *red, float p, int dim, int sem);
int etiqueta_verdadera(int *historial, int s);
int etiqueta_falsa(int *red,int *historial, int S1, int S2, int i, int j, int dim);
int clasificar(int *red,int dim);
int percolacion(int *red, int dim);
int imprimir(int *red,int dim);


//Función principal:
int main(int argc,char*argv[])
{ float p;
  int i, j, t, dim, sem, semm=27000;
  int *red, *s, *ns, *dims;
  float  *p_c, *q_0, *p_max;
  double *ns_p, *s_p, *ns_pviejo;
  char *n_sn;
  FILE *n_s;


  p_c = malloc(6*sizeof(float));
  p_max = malloc(36*sizeof(float));
  dims = malloc(6*sizeof(int));
  n_sn = malloc(sizeof("./Sigma/sigma_0.01.txt"));
  ns_pviejo = malloc(36*sizeof(double));

  *(p_c) = 0.5630;
  *(p_c+1) = 0.5813;
  *(p_c+2) = 0.5878;
  *(p_c+3) = 0.5932;
  *(p_c+4) = 0.5922;
  *(p_c+5) = 0.5927;

  *(dims) = 4;
  *(dims+1) = 8;
  *(dims+2) = 16;
  *(dims+3) = 32;
  *(dims+4) = 64;
  *(dims+5) = 128;

  for(i=0; i<36; i++)
  { *(p_max+i) = 0;
  }

  for(i=0; i<36; i++)
  { *(ns_pviejo+i) = 0;
  }

  for(i=5;i<6;i++)
  { p = 0.10;
    dim = *(dims+i);

    red = malloc(dim*dim*sizeof(int));    //Reserva el espacio necesario para la red.
    s = malloc((dim*dim)*sizeof(int));
    ns = malloc((dim*dim)*sizeof(int));
    ns_p = malloc(dim*dim*sizeof(double));
    s_p = malloc(dim*dim*sizeof(double));
    q_0 = malloc(dim*dim*sizeof(float));

      for(j=0;j<dim*dim;j++)
      { *(ns_p+j) = 0;
      }

      for(sem=0; sem<semm; sem++)
      { poblar(red, *(p_c+4), dim,sem);
        clasificar(red,dim);


        for(j=0;j<dim*dim;j++)
        { *(s+j) = 0;
        }

        for(j=0;j<dim*dim;j++)
        { *(ns+j) = 0;
        }

        for(j=0; j<dim*dim; j++)
        { if(*(red+j))
          { *(s+*(red+j)) += 1;
          }
        }

        for(j=0; j<dim*dim; j++)
        { if(*(s+j))
          { *(ns+*(s+j)) += 1;
          }
        }

        for(j=0; j<dim*dim; j++)
        { *(ns_p+j) += *(ns+j);
        }
      }

      for(j=0;j<dim*dim;j++)
      {
        *(q_0+j) = *(ns_p+j);
        *(q_0+j) /= semm;
      }

    while(p<=1)
    { for(j=0;j<dim*dim;j++)
      { *(ns_p+j) = 0;
      }

      for(j=0;j<dim*dim;j++)
        { *(s_p+j) = 0;
        }

      for(sem=0; sem<semm; sem++)
      { poblar(red, p, dim,sem);
        clasificar(red,dim);


        for(j=0;j<dim*dim;j++)
        { *(s+j) = 0;
        }

        for(j=0;j<dim*dim;j++)
        { *(ns+j) = 0;
        }

        for(j=0; j<dim*dim; j++)
        { if(*(red+j))
          { *(s+*(red+j)) += 1;
          }
        }

        for(j=0; j<dim*dim; j++)
        { if(*(s+j))
          { *(ns+*(s+j)) += 1;
          }
        }

        for(j=0; j<dim*dim; j++)
        { *(ns_p+j) += *(ns+j);
        }

        for(j=0; j<dim*dim; j++)
        { *(s_p+j) += *(s+j);
        }
      }

      for(j=1; j<dim*dim; j++)
      { *(s_p+j) /= semm;
        *(ns_p+j) /= semm;
      }

      for(j=1; j<16; j++)
      { if(*(ns_p+j) > *(ns_pviejo+j))
        { *(p_max+j) = p;
        }
      }

      for(j=1; j<16; j++)
      { *(ns_pviejo+j) = *(ns_p+j);
      }

      for(j=1; j<dim*dim; j++)
      { *(ns_p+j) /= *(q_0+j);
      }

      sprintf(n_sn, "./Sigma/sigma_%0.2f",p);
      n_s = fopen(n_sn, "w");
      for(t=1;t<16;t++)
      {
        fprintf(n_s,"%f\n", *(ns_p+t));
      }
      fclose(n_s);

      /*printf("%f\n", p);
      printf("#################\n");
      for(j=0;j<16;j++)
      { printf("%0.4f ", *(ns_p+j));}
      printf("\n");
      for(j=0;j<16;j++)
      { printf("%0.4f ", *(p_max+j));}
      printf("\n");
      printf("#################\n");
      //printf("\rIn progress %%%0.0f", p*100);
      //fflush(stdout);*/

      p += 0.02;

    }

    for(t=1; t<16; t++)
    { *(p_max+t) -= *(p_c+4);
      *(p_max+t) -= 0.05;
    }

    n_s = fopen("./Sigma/pmax", "w");
    for(t=1; t<16; t++)
    {
      fprintf(n_s,"%f\n", *(p_max+t));
    }
    fclose(n_s);

  }

  free(q_0);
  free(ns);
  free(p_c);
  free(ns_p);
  free(s);
  free(n_sn);
  free(dims);
  free(red);
  free(p_max);
  free(ns_pviejo);

  return 0;
}

//Funciones secundarias:
int poblar(int *red, float p, int dim, int sem)
{ float random;
  int i;
  srand(sem);


  for (i=0;i<dim*dim;i++)               //Toma como rango máximo la cantidad de celdas totales.
    { *(red+i)=0;                       //Asigna por defecto el valor <vacio>
      random=((float)rand())/((float) RAND_MAX);    //Valor aleatorio entre 0 y 1.
      if (random<p)
      {*(red+i)=1;
      }                       //Asigna como <lleno> si el valor aleatorio es menor.
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

int percolacion(int *red, int dim)
{ int i,j,per = 0;

  for(i=0;i<dim;i++)
  { for(j=0;j<dim;j++)
    { if (*(red+i) == *(red+(dim-1)*dim+j) && *(red+i))
      { per = 1;
      }
    }
  }

  return per;
}
