#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define M 	100000
#define R2MIN   0.01
#define R2MAX 	6.26

int main()
{
        int    i;
	double dr2,r2,r6,r12,Vc,V_LJ,F_LJ;
	FILE *fp;

	fp = fopen("tabla.dat","w");

	dr2 = (R2MAX-R2MIN)/(double)M;

        fprintf(fp,"%d\n%lf\n%lf\n",M,R2MIN,R2MAX);
	
	r2 = R2MIN + (double)M*dr2;
	r6 = r2*r2*r2;
	r12= r6*r6;

	Vc = 4.0*(1.0/r12-1.0/r6);

	for(i=0;i<M;i++){
		
		r2 = R2MIN + (double)i*dr2;

		r6 = r2*r2*r2;
		r12= r6*r6;

		V_LJ = 4.0*(1.0/r12-1.0/r6);
		F_LJ = (24.0/r2)*(2.0/r12-1.0/r6);
		fprintf(fp,"%lf %lf %lf %lf\n",sqrt(r2),r2,V_LJ-Vc,F_LJ);
	}	
	 
	fclose(fp);

	return 0;
}
