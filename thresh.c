/*
threshold the enhanced image (after toggle and top-hat) to get binary image
*/
#include "VisXV4.h"          /* VisX structure include file     */
#include "Vutil.h"           /* VisX utility header files       */
#include <stdbool.h>
//#include <float.h>
#include <limits.h>

VXparam_t par[] =       
{                           
{    "if=",    0,   " input file"},
{    "of=",    0,   " output file"},
{    "th=",    0,   " size of structure element"}, //percentage of total pixel range to threshold
{     0,       0,   0}  
};

#define  IVAL   par[0].val
#define  OVAL   par[1].val
#define  THRESH   par[2].val

main(argc, argv)
int argc;
char *argv[];
{
fprintf(stderr,"start thresholding...\n");
Vfstruct (im);                      /* i/o image structure          */
Vfstruct (tm);                      /* temp image structure         */


VXparse(&argc, &argv, par);   /* parse the command line   */

Vfread(&im,IVAL);

Vfnewim(&tm, VX_PBYTE, im.bbx, im.chan);


int thresh=atoi(THRESH);
fprintf(stderr,"threshold used: %d\n",thresh);

int y,x;//image index
int max=INT_MIN,min=INT_MAX;


for(y=im.ylo;y<=im.yhi;y++){
	for(x=im.xlo;x<=im.xhi;x++){
		if(im.u[y][x]>max){
			max=im.u[y][x];
		}else if(im.u[y][x]<min){
			min=im.u[y][x];		
		}	
		
	}
}


int newMin=0,newMax=255;
for(y=im.ylo;y<=im.yhi;y++){
	for(x=im.xlo;x<=im.xhi;x++){
		tm.u[y][x]=(im.u[y][x]-min)*(255/max-min)+newMin;
        }  	
}

fprintf(stderr,"max=%d min=%d threshold=%d\n",max,min,thresh);

for(y=im.ylo;y<=im.yhi;y++){
	for(x=im.xlo;x<=im.xhi;x++){
		if(im.u[y][x]>=thresh){
			tm.u[y][x]=255;
		}else{
			tm.u[y][x]=0;		
		}

	}
}

fprintf(stderr,"thresholding completed\n");

Vfwrite(&tm, OVAL);
exit(0);
}



