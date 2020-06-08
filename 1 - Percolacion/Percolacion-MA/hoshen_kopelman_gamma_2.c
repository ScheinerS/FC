#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define POINTS  20
#define PC      0.5976

int regresion(double *tr,double *p,double *m2,double pc,int n);
int smoothing(double *tr,double *r2medio,double prob,double *pmedio);

int main(void)
{
  int    i,j,n;
  double prob,pmedio,m2,pc,*m,*p,*g;
  FILE   *fp;
 
  n = 0;

  pc = PC;


  fp = fopen("nuevo128.csv","r");

  while (fscanf(fp,"%lf %lf\n",&prob,&m2)==2) n++;

  fclose(fp); 

  m = (double*) malloc(n*sizeof(double));
  p = (double*) malloc(n*sizeof(double));
  g = (double*) malloc(3*sizeof(double));

  fp = fopen("nuevo128.csv","r");

  for(i=0;i<n;i++) 
    {
      j=fscanf(fp,"%lf %lf\n",&prob,&m2);

      *(p+i) = prob;
      *(m+i) = m2;
     
      j++; // useless to avoid warnings
    }

  fclose(fp); 


  i = 0;

  prob = *(p+POINTS);

  fp = fopen("hoshen_kopelman_gamma_menos_128.csv","w");

  while (prob<pc)
    {
       i++;

       pmedio = 0.5*prob;
   
       prob = *(p+i+POINTS);

       pmedio += 0.5*prob;

       regresion(g,p+i,m+i,pc,POINTS);

       fprintf(fp,"%lf %lf %lf\n",pmedio,*(g+2),*(g+0));
    }

  fclose(fp);

  prob = *(p+i);

  while (prob<=pc)
    {
       i++;
       prob = *(p+i);
    }


  fp = fopen("hoshen_kopelman_gamma_mas_128.csv","w");


  while (i<n-POINTS)
    {
       pmedio = 0.5*prob;

       prob = *(p+i+POINTS);

       pmedio += 0.5*prob;

       regresion(g,p+i,m+i,pc,POINTS);

       fprintf(fp,"%lf %lf %lf\n",pmedio,*(g+2),*(g+0));

       i++;
    }

  fclose(fp);

  free(m);
  free(p);
  free(g);
 
  return 1;
}

//-----------FUNCIONES-------------------------------


int regresion(double *tr,double *p,double *m2,double pc,int n)
{
 // *tr es un puntero de dos valores [R^2, c , gamma]
 // *p  es la probabilidad
 // *m  es el momento de segundo orden
 // n   es la cantidad de datos

 int    i,m;
 double r2,dm,dp,sumX=0,sumX2=0,sumY=0,sumY2=0,sumXY=0,a,b,*x,*y;

 x = (double*) malloc(n*sizeof(double));
 y = (double*) malloc(n*sizeof(double));

 m = 0;

 sumX = 0.0;
 sumX2= 0.0;
 sumY = 0.0;
 sumY2= 0.0;
 sumXY= 0.0;

 for (i=0;i<n;i++)
   {
     dm = (*(m2+i));
     dp = fabs((*(p+i))-pc);

     if (dm!=0.0) 
       {
         *(x+m) = log(dp);
         *(y+m) = log(dm);

         sumX  = sumX + *(x+m);
         sumX2 = sumX2 + (*(x+m))*(*(x+m));
         sumY  = sumY + (*(y+m));
         sumY2 = sumY2 + (*(y+m))*(*(y+m));
         sumXY = sumXY + (*(x+m))*(*(y+m));

         m++;
       }
   }

 // y = a+b.x

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


