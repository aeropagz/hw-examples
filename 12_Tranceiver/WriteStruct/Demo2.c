#include <stdio.h>

#include "MyStruct.h"


void main()
{
	
	
	
	struct myStruct strus[]={{"Sinus",50,23,{1,2,3,4}},{"Rechteck",15,33,{5,6,7,8,9}},{"Saegezahn",18,12,{10,11,12,13,14,15}}};
	
	
	
	for(int i=0;i<3;i++)
	{
	 printf("Nachricht:%s i:%d  j:%d values:",strus[i].nachricht,strus[i].i,strus[i].j);
	for(int j=0;j<20;j++)
		{
			printf(" %d ",strus[i].values[j]);	
		}
	printf("\n\n");
	}
	
}
