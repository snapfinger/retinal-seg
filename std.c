/*
standardization for gray-scale image
1. mean
2. standard deviation
*/

#include "VisXV4.h"          /* VisX structure include file     */
#include "Vutil.h"           /* VisX utility header files       */
#include <stdbool.h>


VXparam_t par[] =       
{                           
{    "if=",    0,   " input file"},
{    "of=",    0,   " output file"},

{     0,       0,   0}  
};

#define  IVAL   par[0].val
#define  OVAL   par[1].val


main(argc, argv)
int argc;
char *argv[];
{
fprintf(stderr,"start\n");
Vfstruct (im);                      
Vfstruct (tm);                     


VXparse(&argc, &argv, par);   /* parse the command line   */

Vfread(&im,IVAL);


long sum=0; //for mean
float sum_sq=0;//for standard deviation
float mean=0;
float var=0; //variance
float std=0; //standard deviation


Vfembed(&tm,&im,0,0,0,0); //for min

Vfembed(&tm,&im,0,0,0,0); //for output

int y,x;//image index


//compute mean
for(y=im.ylo;y<=im.yhi;y++){	
	for(x=im.xlo;x<=im.xhi;x++){
		sum+=im.u[y][x];
	}
}

int totalNum=(im.yhi-im.ylo+1)*(im.xhi-im.xlo+1);
mean=(float)(sum/totalNum);

//compute standard deviation
for(y=im.ylo;y<=im.yhi;y++){	
	for(x=im.xlo;x<=im.xhi;x++){
		float curPixel=(float)im.u[y][x];
		sum_sq+=(curPixel-mean)*(curPixel-mean);		
	}
}

var=sum_sq/(float)totalNum;
std=sqrt(var);

fprintf(stderr,"sum=%ld \n",sum);
fprintf(stderr,"sum_sq=%.2f \n",sum_sq);
fprintf(stderr,"total pixel number=%d \n",totalNum);
fprintf(stderr,"mean=%.2f \nstadard deviation=%.2f \n",mean,std);
fprintf(stderr,"var=%f \n",var);

for(y=tm.ylo;y<=tm.yhi;y++){	
	for(x=tm.xlo;x<=tm.xhi;x++){
		float curPixel=(float)im.u[y][x];
		float tmpPixel=curPixel-mean;
		tm.f[y][x]=tmpPixel/std;
	}
}

Vfwrite(&tm, OVAL);
exit(0);
}

