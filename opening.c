/*
implement the opening (first erosion, then dilation) for gray-scale image
*/
#include "VisXV4.h"          /* VisX structure include file     */
#include "Vutil.h"           /* VisX utility header files       */
#include <stdbool.h>




VXparam_t par[] =       
{                           
{    "if=",    0,   " input file"},
{    "of=",    0,   " output file"},
{    "s=",    0,   " size of structure element"}, //disk structure element default
{     0,       0,   0}  
};

#define  IVAL   par[0].val
#define  OVAL   par[1].val
#define  SIZE   par[2].val

main(argc, argv)
int argc;
char *argv[];
{
fprintf(stderr,"start\n");
Vfstruct (im);                      /* i/o image structure          */
Vfstruct (tm1);                      /* temp image structure         */
Vfstruct (tm2);                      /* temp image structure         */
Vfstruct (tm3);                      /* temp image structure         */

VXparse(&argc, &argv, par);   /* parse the command line   */

Vfread(&im,IVAL);


Vfembed(&tm1,&im,0,0,0,0); //for min
Vfembed(&tm2,&im,0,0,0,0); //for max
Vfembed(&tm3,&im,0,0,0,0); //for output

fprintf(stderr,"construction done");

int radius=atoi(SIZE);
fprintf(stderr,"radius size: %d\n",radius);

int y,x;//image index


//first min (erode)
for(y=im.ylo;y<=im.yhi;y++){
	int y0=im.ylo>y-radius?im.ylo:y-radius;
	int y1=im.yhi<y+radius?im.yhi:y+radius;
	
	for(x=im.xlo;x<=im.xhi;x++){
		int x0=im.xlo>x-radius?im.xlo:x-radius;
		int x1=im.xhi<x+radius?im.xhi:x+radius;
		
		int minVal=im.u[y][x];
		
		int u,v;
   
		for(u=y0;u<=y1;u++){
			for(v=x0;v<=x1;v++){
				if((y-u)*(y-u)+(x-v)*(x-v)<=radius*radius && im.u[u][v]<minVal){
					minVal=im.u[u][v];
				}
			}
		}
		
		tm1.u[y][x]=minVal;
	}
}

fprintf(stderr,"start max...\n");

//max filter (dilate)
for(y=tm1.ylo;y<=tm1.yhi;y++){
	int y0=tm1.ylo>y-radius?tm1.ylo:y-radius;
	int y1=tm1.yhi<y+radius?tm1.yhi:y+radius;
	
	for(x=tm1.xlo;x<=tm1.xhi;x++){
		int x0=tm1.xlo>x-radius?tm1.xlo:x-radius;
		int x1=tm1.xhi<x+radius?tm1.xhi:x+radius;
		
		int maxVal=tm1.u[y][x];
		
		int u,v;
		for(u=y0;u<=x1;u++){
			for(v=y0;v<=y1;v++){
				if((y-u)*(y-u)+(x-v)*(x-v)<=radius*radius && tm1.u[u][v]>maxVal){
					maxVal=tm1.u[u][v];
				}
			}
		}
		
		tm2.u[y][x]=maxVal;
	}
}


fprintf(stderr,"opening completed\n");

Vfwrite(&tm2, OVAL);
exit(0);
}


