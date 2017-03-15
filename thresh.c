/*
threshold the enhanced image (after toggle and top-hat) to get binary image
*/
#include "VisXV4.h"          /* VisX structure include file     */
#include "Vutil.h"           /* VisX utility header files       */
#include <stdbool.h>
#include <float.h>

VXparam_t par[] =       
{                           
{    "if=",    0,   " input file"},
{    "of=",    0,   " output file"},
{    "p=",    0,   " size of structure element"}, //percentage of total pixel range to threshold
{     0,       0,   0}  
};

#define  IVAL   par[0].val
#define  OVAL   par[1].val
#define  PST   par[2].val

main(argc, argv)
int argc;
char *argv[];
{
fprintf(stderr,"start\n");
Vfstruct (im);                      /* i/o image structure          */
Vfstruct (tm);                      /* temp image structure         */


VXparse(&argc, &argv, par);   /* parse the command line   */

Vfread(&im,IVAL);

Vfnewim(&tm, VX_PBYTE, im.bbx, im.chan);

float percent=strtof(PST,NULL);
fprintf(stderr,"percentage: %f\n",percent);

int y,x;//image index
float max=-FLT_MAX,min=FLT_MAX;

//first min (erode)
for(y=im.ylo;y<=im.yhi;y++){
	for(x=im.xlo;x<=im.xhi;x++){
		if(im.f[y][x]>max){
			max=im.f[y][x];
		}else if(im.f[y][x]<min){
			min=im.f[y][x];		
		}	
		
	}
}

float threshold=min+(max-min)*percent;

for(y=im.ylo;y<=im.yhi;y++){
	for(x=im.xlo;x<=im.xhi;x++){
		if(im.f[y][x]>=threshold){
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



