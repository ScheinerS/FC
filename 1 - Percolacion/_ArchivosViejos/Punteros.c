#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
// Lo primero que vamos a hacer es crear una matríz. Para hacer eso hacemos creamos un puntero llamado M
//cuya cantidad de elementos sea la misma que la de la matríz que queremos escribir.
//Por ejemplo para matrices de 2x2.

float *M; //definimos el puntero como float para que pueda haber números decimales en la matriz.
M = (float*) malloc(4 * sizeof(float)); //Le asignamos el tamaño al puntero.
//Como los punteros trabajan con la memoria, al asignar el tamaño de un puntero uno tiene que hacerlo
//en función de parámetros de la memoria. malloc(N*sizeof(float)) significa que mi puntero va a tener
//el tamaño correspondiente a la cantidad de memoria que ocupa almacenar N números de punto flotante.
//Si quiero usar sólamente números enteros, uso sizeof(int) en lugar de sizeof(float).

//El paso siguiente es llenar todos los elementos de matriz con los números deseados:
//Esto se hace de la siguiente manera:



*(M + (0*2 + 0)) = 4;
*(M + (0*2 + 1)) = 1;
*(M + (1*2 + 0)) = 3;
*(M + (1*2 + 1)) = 2;

// *(M + j) significa en criollo: "El contenido de la posición de memoria M + j". Siempre que quieran asignarle
// un valor a algún elemento del puntero deben referirse a el como *(M + algo). Sino estarían redefiniendo la
// posición de memoria, y eso en general nadie lo quiere hacer. 

//La notación parece rara, pero tiene justificación.
//Estamos acostumbrados a pensar las matrices como arrays de dos dimensiones. Pero el puntero tiene una dimensión
//como un vector. Por lo tanto si queremos el elemento M{i,j} de una matriz de NxN, en el puntero va a ser el elemento
//M[(i)*N + (j)]. Entonces el elemento 00 de la matriz es el 0 del puntero.

//imprimo la matriz para ver que sea la que yo quiero:
int i,j;
for(i = 0; i < 2; i++)
{
  for(j = 0; j < 2; j++)
  {
    printf("%f\t",*(M + (i*2) + j)); // \t es tabular. Para que me queden espaciados los elementos de cada fila en pantalla.
  }
  printf("\n");// Paso al renglón siguiente de la pantalla para la próxima fila.
}

//Ahora que vimos que la matriz está bien definida vamos a transponerla. Para eso nos creamos otro puntero del mismo tamaño
// y lo llamamos Mt, por matriz transpuesta. (Recomendación, siempre usen los nombres más explicitos posibles para las
//variables, sin caer en lo absurdo, porque sino después uno se pierde en su programa).

float *Mt;
Mt= (float*) malloc(4 * sizeof(float));

//Para no hacer la transposición elemento por elemento a mano, vamos a usar un ciclo "for":
for(i = 0; i < 2; i++)
{
  for(j = 0; j < 2; j++)
  {
    *(Mt + 2*i + j) = *(M + 2*j + i); //Cambiamos el elemento ij por el ji.
  }
}
printf("\n"); // imprimimos un renglón vacío para que no nos queden pegadas las dos matrices cuando las imprimamos.
for(i = 0; i < 2; i++)
{
  for(j = 0; j < 2; j++)
  {
    printf("%f\t",*(Mt + (i*2) + j));
  }
  printf("\n");
}

  return 0;
}
