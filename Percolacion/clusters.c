/*Vamos a identificar grupos de clusters en una tira de NxN.
Voy a usar el programita poblarlared2 para generar la matriz de unos y ceros*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define SEED 260868 /*no tengo muy en claro ésto*/
#define N    3
#define PROB 0.5

double myrandom(double prob);

int min(int s1,int s2);

int max(int s1,int s2);

int main()
{
	int    i,s,s1,s2,frag,m,M;
	
	double prob,r;
	
	int *red,*clase;
	
	s =0;

	s1=0;

	s2=0;
	
	red  = (int*)malloc((N*N)*sizeof(int));
	
	clase= (int*)malloc((N*N)*sizeof(int));

    prob=PROB;

	srand(SEED);

	for(i=0;i<N*N;i++) /*generamos la tira de 1 y 0*/
    {
        r=myrandom(prob);
	      
	    if(r<prob) *( red + i )=0;
	      
	    else       *( red + i )=1;
       

        printf("%i",*( red + i ));
    }
    
  
     for(i=0;i<N;i++)
     {
        
        if (s) /*funcion actualizar*/
        {
    
         while (*(clase+s)<0) 

         s=-(*(clase+s));
    
         *(red+i)=s;
    
         *(clase+s)=s;
        }
       
        else
        {
         *(red+i)=frag;
       
         *(clase+frag)=frag; /* por seguridad!*/
       
         frag++;
        }

       /*funcion etiqueta_falsa*/
     
       s1= *(red + i - N); /*vecino de arriba*/

       s2= *(red + i - 1); /*vecino de la izquierda*/

       while (*(clase+s1)<0) s1=-(*(clase+s1)); /*etiqueta s1 verdadera*/
     
       while (*(clase+s2)<0) s2=-(*(clase+s2)); /*etiqueta s2 verdadera*/
     
       m=min(s1,s2);
     
       M=max(s1,s2);
     
       *(red+i)=m;
     
       *(clase+m)=m;
     
       if (m<M) *(clase+M)=-m; 
     
       else *(clase+M)=m;    
     
     } 
     
     /*Repasa toda la tira corrigiendo los valores incorrectos*/
     
       for(i=0;i<N*N;i++)
      {
         s=*(red+i);
         
         while (*(clase+s)<0) 

         	s=-(*(clase+s));
            
            *(red+i)=*(clase+s);
      
      }
   
             printf("%i\n",*( clase + s ));

      return 1;
}

/*int minimo(int s1,int s2)
{
   int MIN;

   MIN=(int) min(int s1,int s2);

   return MIN;
}

int maximo(int s1,int s2)
{
   int MAX;

   MAX=(int) max(int s1,int s2);

   return MAX;
}*/

double myrandom(double prob)
{
	double r;

	r=(double)rand()/(double)RAND_MAX;

	return r;
}

int max(int s1, int s2) 
{
   int M;
   if (s1 > s2)
      M = s1;
   else
      M = s2;
   return M; 
}

int min(int s1, int s2) 
{
   int m;
   if (s1 > s2)
      m = s2;
   else
      m = s1;
   return m; 
}